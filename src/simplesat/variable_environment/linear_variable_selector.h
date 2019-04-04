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

#ifndef SRC_VARIABLE_ENVIRONMENT_LINEAR_VARIABLE_SELECTOR_H
#define SRC_VARIABLE_ENVIRONMENT_LINEAR_VARIABLE_SELECTOR_H

#include "src/simplesat/variable_environment/variable_environment.h"
#include "src/simplesat/variable_environment/variable_selector.h"

namespace simplesat {

class LinearVariableSelector : public VariableSelector {
  public:
  LinearVariableSelector(variable_id max_id);
  VariableIterator cbegin() const override;
  VariableIterator cend() const override;
  
  VariableState recommend_assignment(variable_id id) const override { return VariableState::SFALSE; }

  // Do nothing to recalculate for linear selection.
  void recalculate(const cnf::Or& learned_term) override 
  { };
  private:
  std::vector<variable_id> order_;
};

} // namespace simplesat
#endif // SRC_VARIABLE_ENVIRONMENT_LINEAR_VARIABLE_SELECTOR_H