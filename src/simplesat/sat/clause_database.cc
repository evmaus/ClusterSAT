// Copyright 2019 Google LLC
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.


#include "src/simplesat/sat/clause_database.h"


namespace simplesat {
ClauseDatabase::ClauseDatabase(cnf::And& term, 
                                std::unique_ptr<VariableEnvironmentStack>& env, 
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
    
    int i = 0;
    for (auto it = learned_clauses_.cbegin(); 
            it != learned_clauses_.cend() && 
            (i < learned_clauses_.count() - keep_terms); 
            it++) {
      if (compacting_policy_->remove_term(i, *it)) {
        it = learned_clauses_.erase(it);
      }
      i++;
    }
  }
}

std::list<cnf::Or*> ClauseDatabase::unit_terms() {
  std::list<cnf::Or*> units = term_.unit_terms(*env_stack_);
  std::list<cnf::Or*> learned_units = learned_clauses_.unit_terms(*env_stack_);
  for (auto unit : learned_units) {
    units.push_back(unit);
  }
  return units;
}

bool ClauseDatabase::has_empty() const {
  return term_.has_empty(*env_stack_) || learned_clauses_.has_empty(*env_stack_);
}

cnf::Or ClauseDatabase::next_empty() const {
  if (term_.has_empty(*env_stack_)) {
    return term_.next_empty(*env_stack_);
  } else {
    return learned_clauses_.next_empty(*env_stack_);
  }
}

VariableRecommendation ClauseDatabase::next_unbound() {
  return env_stack_->next_unbound();
}

void ClauseDatabase::assign(variable_id var, VariableState state) {
  return env_stack_->assign(var, state);
}

void ClauseDatabase::push() {
  env_stack_->push();
}

void ClauseDatabase::pop() {
  env_stack_->pop();
}

void ClauseDatabase::backtrack(int backtrack_level) {
  env_stack_->Backtrack(backtrack_level);
}
} // namespace simplesat