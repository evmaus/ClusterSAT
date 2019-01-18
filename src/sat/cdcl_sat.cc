#include "src/sat/cdcl_sat.h"

#include <vector>
#include <string>
#include <chrono>
#include <future>
#include <iostream>

#include "src/common/log.h"
#include "src/cnf/cnf_environment_stack.h"
#include "src/cnf/cnf_variable_environment.h"
#include "src/sat/cdcl_trace.h"
namespace tribblesat {

CDCLSatStrategy::CDCLSatStrategy(uint64_t timeout) 
: timeout_ms_(timeout)
{ }

void UnitPropagate(const cnf::And& term, cnf::VariableEnvironment& env, int decision_level, CDCLTrace& trace) {
  while(term.has_unit(env))
  {
    auto unit_terms = term.unit_terms(env);
    std::vector<std::pair<cnf::Variable, cnf::VariableState>> assignments;
    LOG(LogLevel::VERBOSE, "Identified terms count " + std::to_string(unit_terms.size()));
    for (auto unit : unit_terms) {
      LOG(LogLevel::VERBOSE, std::to_string(decision_level) + " Identified unit: " + unit.to_string());
      cnf::Variable variable = unit.first_unassigned(env);
      auto state = variable.negated() ? cnf::VariableState::SFALSE : cnf::VariableState::STRUE;
      assignments.push_back(std::pair<cnf::Variable, cnf::VariableState>(variable, state));
      trace.AddUnitPropagation(decision_level, variable.id(), state, unit);
    }

    for (auto assign : assignments) {
      env.assign(assign.first.id(), assign.second);
      LOG(LogLevel::VERBOSE, std::to_string(decision_level) + "Assigned " + assign.first.to_string() + " -> " + cnf::VariableEnvironment::StateToString(assign.second));
    }
  }
}

int AnalyzeConflict(int decision_level, const cnf::And& term, cnf::VariableEnvironment& env, 
  cnf::And& learned_clauses,
  CDCLTrace& trace) 
{
  std::pair<int, cnf::Or> result = trace.LearnClauses(decision_level, term, env);
  learned_clauses.add_term(result.second);
  return result.first;
}

void PickBranchVariableAndAssign(uint32_t& current_decision_level, const cnf::And& term,
  cnf::VariableEnvironmentStack& env_stack, 
  CDCLTrace& trace
)
{
  if (!term.has_empty(env_stack)) {
    // Pick branch variable.
    cnf::variable_id next_var = env_stack.first_unbound();
    current_decision_level++;
    // Push stack and set branch variable.
    env_stack.push();
    auto state = cnf::VariableEnvironment::RandomState();

    LOG(LogLevel::VERBOSE, std::to_string(current_decision_level) + 
      " Arbitrary assignment: Assigning " + std::to_string(next_var) + " to " + 
      cnf::VariableEnvironment::StateToString(state));
    trace.AddAssignmentChoice(current_decision_level, next_var, state);
    env_stack.assign(next_var, state);
  }
}


SatResultType CDCLSatStrategy::DetermineCnfSatInternal(
    const cnf::And& term, std::atomic_bool& run) const 
{
  LOG(LogLevel::VERBOSE, "Starting CDCL on " + term.to_string());

  std::vector<cnf::Or> terms;
  cnf::And learned_clauses(terms);
  CDCLTrace trace;
  // Create variable environment.
  cnf::VectorVariableEnvironment env(term.variable_count());
  UnitPropagate(term, env, 0, trace);
  cnf::VariableEnvironmentStack env_stack(env);
  uint32_t current_decision_level = 0;
  
  while (run){
    if (term.satisfied(env_stack)) {
      LOG(LogLevel::VERBOSE, "Finished, returning SAT");
      return SatResultType::SAT;
    } 
    else 
    {
      // Try unit propagation
      UnitPropagate(term, env_stack, current_decision_level, trace);
      UnitPropagate(learned_clauses, env_stack, current_decision_level, trace);
      PickBranchVariableAndAssign(current_decision_level, term, env_stack, trace);
      UnitPropagate(term, env_stack, current_decision_level, trace);
      UnitPropagate(learned_clauses, env_stack, current_decision_level, trace);

      if (term.has_empty(env_stack)) {
        LOG(LogLevel::VERBOSE, "Empty term: " + term.next_empty(env_stack).to_string());
        int conflict_level = AnalyzeConflict(current_decision_level, term, env_stack, learned_clauses, trace);
        LOG(LogLevel::VERBOSE, "Backtracking: " + std::to_string(conflict_level));
        LOG(LogLevel::VERBOSE, "Learned Clauses: " + learned_clauses.to_string());
        
        if (conflict_level < 0) {
          LOG(LogLevel::VERBOSE, "Finished, returning UNSAT");
          return SatResultType::UNSAT;
        }
        while (current_decision_level > conflict_level) {
          env_stack.pop();
          current_decision_level--;
        }
        trace.Backtrack(current_decision_level);
        LOG(LogLevel::VERBOSE, "New environment after backtracking: " + env_stack.to_string());

      }
    }
  }

  return SatResultType::UNKNOWN;
}

SatResultType CDCLSatStrategy::DetermineCnfSat(const cnf::And& term) const 
{
  std::atomic_bool run;
  run = true;
  auto future = std::async(
    std::launch::async, [this, &term, &run]() {
      return DetermineCnfSatInternal(term, run);
    }
  );
  if (timeout_ms_ != 0)
  {
    auto status = future.wait_for(std::chrono::milliseconds(timeout_ms_));
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