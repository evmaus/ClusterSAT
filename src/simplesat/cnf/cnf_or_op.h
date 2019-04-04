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

#ifndef SRC_CNF_CNF_OR_OP_H
#define SRC_CNF_CNF_OR_OP_H

#include "src/simplesat/cnf/cnf_variable.h"
#include <vector>

namespace simplesat {
namespace cnf {

enum TermState {
  SAT,
  UNSAT,
  UNIT,
  UNRESOLVED
};

class Or {
  public:
  Or() {}
  Or(std::vector<Variable> variables);
  TermState term_state(const VariableEnvironment& env);
  variable_id max_variable() const;
  Variable first_unassigned(const VariableEnvironment& env);
  Variable last_unassigned(const VariableEnvironment& env);
  std::string to_string() const;

  // Combine terms and remove units.
  cnf::Or combine_with(cnf::Or other_term);


  std::vector<Variable>::const_iterator cbegin() const { return variables_.cbegin(); }
  std::vector<Variable>::const_iterator cend() const { return variables_.cend(); }
  std::vector<Variable>::iterator begin() { return variables_.begin(); }
  std::vector<Variable>::iterator end() { return variables_.end(); }
  int count() const { return variables_.size(); }

  private:
  std::vector<Variable> variables_;
  int first_watched_literal_;
  int second_watched_literal_;
};
} // namespace cnf
} // namespace simplesat


#endif