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

#ifndef SRC_CNF_CNF_VARIABLE_H
#define SRC_CNF_CNF_VARIABLE_H

#include "src/simplesat/variable_environment/variable_environment.h"

namespace simplesat {
namespace cnf {

class Variable {
  public:
  Variable(variable_id variable);
  Variable(variable_id variable, bool negated);
  VariableState GetValueInEnvironment(const VariableEnvironment& env) const;

  variable_id id() const { return variable_; }
  bool negated() const { return negated_; }

  Variable negate() const { return Variable(variable_, !negated_); }
  std::string to_string() const;

  private:
  variable_id variable_;
  bool negated_;
};
} // namespace cnf
} // namespace simplesat

#endif