/*
 * Copyright 2019 Google LLC
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef SRC_SAT_CLAUSE_DATABASE_H
#define SRC_SAT_CLAUSE_DATABASE_H

#include "src/simplesat/cnf/cnf_and_op.h"
#include "src/simplesat/variable_environment/environment_stack.h"
#include "src/simplesat/sat/compacting_policy.h"

namespace simplesat {

class ClauseDatabase {
  public:
  ClauseDatabase(cnf::And& term, 
                  std::unique_ptr<VariableEnvironmentStack>& env, 
                  std::unique_ptr<CompactingPolicy>& compacting_policy);
  
  void add_term(cnf::Or term);
  void compact(int decision_level);

  std::list<cnf::Or*> unit_terms();
  const cnf::And& learned_clauses() const { return learned_clauses_; }
  std::unique_ptr<VariableEnvironmentStack>& environment() { return env_stack_; }

  bool has_empty() const;
  cnf::Or next_empty() const;

  VariableRecommendation next_unbound();
  void assign(variable_id var, VariableState state);

  void push();
  void pop();
  void backtrack(int backtrack_level);

  private:
  cnf::And& term_;
  cnf::And learned_clauses_;
  std::unique_ptr<VariableEnvironmentStack>& env_stack_;
  const std::unique_ptr<CompactingPolicy>& compacting_policy_;
};
} // namespace simplesat
#endif // SRC_SAT_CLAUSE_DATABASE_H