#include "src/sat/cdcl_sat.h"

#include <vector>
#include <string>
#include <chrono>
#include <future>
#include <iostream>

#include "src/common/log.h"
#include "src/variable_environment/environment_stack.h"
#include "src/variable_environment/variable_environment.h"
#include "src/variable_environment/linear_variable_selector.h"
#include "src/sat/cdcl_trace.h"
#include "src/sat/clause_database.h"
#include "src/common/stats.h"

namespace tribblesat {

CDCLSatStrategy::CDCLSatStrategy(CDCLConfiguration config) 
: config_(config)
{ }

void UnitPropagate(ClauseDatabase& clause_db,
  int decision_level, 
  CDCLTrace& trace,
  Stats& stats) 
{
  stats.StartBCP();
  auto unit_terms = clause_db.unit_terms();
  while(!unit_terms.empty()) {
    stats.BCPClauses(unit_terms.size());
    std::vector<std::pair<cnf::Variable, VariableState>> assignments;
    LOG(LogLevel::VERBOSE, "Identified terms count " + std::to_string(unit_terms.size()));
    for (auto unit : unit_terms) {
      LOG(LogLevel::VERBOSE, std::to_string(decision_level) + " Identified unit: " + unit.to_string());
      cnf::Variable variable = unit.first_unassigned(clause_db.environment());
      auto state = variable.negated() ? VariableState::SFALSE : VariableState::STRUE;
      assignments.push_back(std::pair<cnf::Variable, VariableState>(variable, state));
      trace.AddUnitPropagation(decision_level, variable.id(), state, unit);
    }

    for (auto assign : assignments) {
      clause_db.assign(assign.first.id(), assign.second);
      LOG(LogLevel::VERBOSE, std::to_string(decision_level) + "Assigned " + assign.first.to_string() + " -> " + VariableEnvironment::StateToString(assign.second));
    }

    unit_terms = clause_db.unit_terms();
  }
  stats.EndBCP();
}

int AnalyzeConflict(int decision_level, 
  ClauseDatabase& db, 
  VariableEnvironment& env, 
  CDCLTrace& trace,
  std::unique_ptr<VariableSelector>& selector,
  Stats& stats) 
{
  stats.StartConflictLearning();
  std::pair<int, cnf::Or> result = trace.LearnClauses(decision_level, db, env);
  stats.LearnConflictSize(result.second.count());
  selector->recalculate(result.second);
  db.add_term(result.second);
  stats.EndConflictLearning();
  return result.first;
}

void PickBranchVariableAndAssign(uint32_t& current_decision_level, ClauseDatabase& clause_db,
  const std::unique_ptr<VariableSelector>& variable_selector,
  CDCLTrace& trace,
  Stats& stats
)
{
  stats.StartVariablePick();
  if (!clause_db.has_empty()) {
    // Pick branch variable.
    VariableRecommendation next_var = clause_db.next_unbound();
    current_decision_level++;
    // Push stack and set branch variable.
    clause_db.push();

    LOG(LogLevel::VERBOSE, std::to_string(current_decision_level) + 
      " Arbitrary assignment: Assigning " + std::to_string(next_var.first) + " to " + 
      VariableEnvironment::StateToString(next_var.second));
    trace.AddAssignmentChoice(current_decision_level, next_var.first, next_var.second);
    clause_db.assign(next_var.first, next_var.second);
  }
  stats.EndVariablePick();
}


SatResult CDCLSatStrategy::DetermineCnfSatInternal(
    const cnf::And& term, std::atomic_bool& run) const 
{
  Stats stats;
  stats.StartSAT();
  LOG(LogLevel::VERBOSE, "Starting CDCL on " + term.to_string());

  std::vector<cnf::Or> terms;
  variable_id term_count = term.variable_count();
  CDCLTrace trace;
  // Create variable environment.
  std::unique_ptr<VariableSelector> selector = config_.AllocateNewVariableSelector(term);
  std::unique_ptr<CompactingPolicy> compact_policy = config_.AllocateNewCompactingPolicy(term);
  VariableEnvironmentStack env_stack(term_count, selector);

  ClauseDatabase clause_db(term, env_stack, compact_policy);
  UnitPropagate(clause_db, 0, trace, stats);
  uint32_t current_decision_level = 0;
  
  while (run){
    if (term.satisfied(env_stack)) {
      LOG(LogLevel::VERBOSE, "Finished, returning SAT");
      stats.EndSAT();
      LOG(LogLevel::INFORMATIONAL, stats.to_string());
      return SatResult(SatResultType::SAT, &env_stack);
    } 
    else 
    {
      // Try unit propagation
      UnitPropagate(clause_db, current_decision_level, trace, stats);
      PickBranchVariableAndAssign(current_decision_level, clause_db, selector, trace, stats);
      UnitPropagate(clause_db, current_decision_level, trace, stats);

      if (clause_db.has_empty()) {
        stats.Conflict();
        LOG(LogLevel::VERBOSE, "Empty term: " + clause_db.next_empty().to_string());
        int conflict_level = AnalyzeConflict(current_decision_level, clause_db, env_stack, trace, selector, stats);
        LOG(LogLevel::VERBOSE, "Backtracking: " + std::to_string(conflict_level));
        LOG(LogLevel::VERBOSE, "Learned Clauses: " + clause_db.learned_clauses().to_string());
        
        if (conflict_level < 0) {
          LOG(LogLevel::VERBOSE, "Finished, returning UNSAT");
          stats.EndSAT();
          LOG(LogLevel::INFORMATIONAL, stats.to_string());
          return SatResult(SatResultType::UNSAT, nullptr);
        }

        // Backtrack
        clause_db.compact(current_decision_level);
        current_decision_level = conflict_level;
        env_stack.Backtrack(current_decision_level);
        trace.Backtrack(current_decision_level);
        // End backtrack
        LOG(LogLevel::VERBOSE, "New environment after backtracking: " + env_stack.to_string());
      }
    }
  }

  return SatResult(SatResultType::UNKNOWN, nullptr);
}

SatResult CDCLSatStrategy::DetermineCnfSat(const cnf::And& term) const 
{
  std::atomic_bool run;
  run = true;
  auto future = std::async(
    std::launch::async, [this, &term, &run]() {
      return DetermineCnfSatInternal(term, run);
    }
  );
  if (config_.timeout_ms() != 0)
  {
    auto status = future.wait_for(std::chrono::milliseconds(config_.timeout_ms()));
    if (status == std::future_status::timeout)
    {
      run = false;
      future.wait();
      return future.get();
    } 
    else 
    {
      return future.get();
    } 
  } else {
    future.wait();
    return future.get();
  }
}

} // namespace tribblesat