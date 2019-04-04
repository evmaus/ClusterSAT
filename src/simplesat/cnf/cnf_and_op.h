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

#ifndef SRC_CNF_CNF_AND_OP_H
#define SRC_CNF_CNF_AND_OP_H

#include "src/simplesat/cnf/cnf_or_op.h"
#include <list>

namespace simplesat {
namespace cnf {
class And {
  public:
  And() {}
  And(std::list<Or> terms);
  std::string to_string() const;

  void add_term(Or term);
  bool satisfied(const VariableEnvironment& env) const;
  variable_id variable_count() const;
  bool has_unit(const VariableEnvironment& env) const;
  Or next_unit(const VariableEnvironment& env) const;
  bool has_empty(const VariableEnvironment& env) const;
  Or next_empty(const VariableEnvironment& env) const;
  std::list<Or*> unit_terms(const VariableEnvironment& env);
  std::list<Or*> empty_terms(const VariableEnvironment& env);

  std::list<Or>::const_iterator cbegin() const { return terms_.cbegin(); }
  std::list<Or>::const_iterator cend() const { return terms_.cend(); }
  std::list<Or>::const_iterator erase(std::list<Or>::const_iterator it) { return terms_.erase(it); }
  int count() const { return terms_.size(); }

  private:
  std::list<Or> terms_;

};
} // namespace cnf
} // namespace simplesat
#endif