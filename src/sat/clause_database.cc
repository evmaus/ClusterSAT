
#include "src/sat/clause_database.h"

#include "src/common/log.h"

namespace tribblesat {
ClauseDatabase::ClauseDatabase(const cnf::And& term, 
                                VariableEnvironmentStack& env, 
                                std::unique_ptr<CompactingPolicy>& compacting_policy)
  : term_(term), env_stack_(env), compacting_policy_(compacting_policy)
{ }

void ClauseDatabase::add_term(cnf::Or term) {
  learned_clauses_.add_term(term);
}

void ClauseDatabase::compact(int decision_level) {
  if (compacting_policy_->should_compact(decision_level)) {
    // If we are below the limit, we keep all terms.
    int keep_terms = compacting_policy_->keep_last();
    if (learned_clauses_.count() <= keep_terms) {
      return;
    }
    
    LOG(LogLevel::VERBOSE, "test1");
    int i = 0;
    for (auto it = learned_clauses_.cbegin(); 
            it != learned_clauses_.cend() && 
            (i < learned_clauses_.count() - keep_terms); 
            it++) {
      if (compacting_policy_->remove_term(i, *it)) {
        LOG(LogLevel::VERBOSE, "test " + std::to_string(i) +" " +(*it).to_string());
        it = learned_clauses_.erase(it);
      }
      i++;
    }
  }
}

std::list<cnf::Or> ClauseDatabase::unit_terms() const {
  std::list<cnf::Or> units = term_.unit_terms(env_stack_);
  std::list<cnf::Or> learned_units = learned_clauses_.unit_terms(env_stack_);
  for (auto unit : learned_units) {
    units.push_back(unit);
  }
  return units;
}

bool ClauseDatabase::has_empty() const {
  return term_.has_empty(env_stack_) || learned_clauses_.has_empty(env_stack_);
}

cnf::Or ClauseDatabase::next_empty() const {
  if (term_.has_empty(env_stack_)) {
    return term_.next_empty(env_stack_);
  } else {
    return learned_clauses_.next_empty(env_stack_);
  }
}

VariableRecommendation ClauseDatabase::next_unbound() {
  return env_stack_.next_unbound();
}

void ClauseDatabase::assign(variable_id var, VariableState state) {
  return env_stack_.assign(var, state);
}

void ClauseDatabase::push() {
  env_stack_.push();
}

void ClauseDatabase::pop() {
  env_stack_.pop();
}

void ClauseDatabase::backtrack(int backtrack_level) {
  env_stack_.Backtrack(backtrack_level);
}
} // namespace tribblesat