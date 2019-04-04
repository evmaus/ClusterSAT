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

#ifndef SRC_CNF_CNF_VECTOR_ENVIRONMENT_H
#define SRC_CNF_CNF_VECTOR_ENVIRONMENT_H

#include <vector>
#include "src/simplesat/variable_environment/variable_environment.h"
#include "src/simplesat/variable_environment/variable_selector.h"

namespace simplesat {

class VectorVariableEnvironment : public VariableEnvironment {
  public:
  
  VectorVariableEnvironment(variable_id count, VariableState state); // Creates an environment with only variables set to state.
  VectorVariableEnvironment(variable_id count, const VariableSelector& selector); // Creates an environment with n unbound variables
  VectorVariableEnvironment(variable_id count, VariableState state, const VariableSelector& selector); // Creates an environment with only variables set to state.

  void assign(variable_id variable, VariableState value) override;
  VariableState lookup(variable_id variable) const override;
  variable_id count() const override { return count_; } 
  VariableRecommendation next_unbound() const override;
  std::string to_string() const override;
  
  std::vector<int> assignments_by_id() const override;

  static VariableState Not(VariableState state);
  private:
  variable_id count_;
  std::vector<VariableState> assignments_;
  const VariableSelector& selector_;
};

} // namespace simplesat
#endif // SRC_CNF_CNF_VECTOR_ENVIRONMENT_H