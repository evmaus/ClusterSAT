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

#ifndef SRC_CNF_CNF_ENVIRONMENT_STACK_H
#define SRC_CNF_CNF_ENVIRONMENT_STACK_H

#include <stack>
#include <string>
#include <map>

#include "src/simplesat/variable_environment/variable_environment.h"
#include "src/simplesat/variable_environment/variable_selector.h"

namespace simplesat {

using VariableStackEntry = std::pair<int, VariableState>;

class VariableEnvironmentStack : public VariableEnvironment {
  public:
  VariableEnvironmentStack(variable_id count, const std::unique_ptr<VariableSelector>& selector);
  virtual void push();
  virtual void pop();
  virtual int current_level() const;

  virtual variable_id count() const override;
  virtual void assign(variable_id variable, VariableState value) override;
  virtual VariableState lookup(variable_id variable) const override;
  virtual VariableRecommendation next_unbound() const override;
  virtual std::string to_string() const override;
  virtual void Backtrack(int new_level);
  virtual std::vector<int> assignments_by_id() const override;
  private:
  uint32_t current_depth_ = 0;
  variable_id count_;
  std::map<variable_id, VariableStackEntry> variable_map_;
  const std::unique_ptr<VariableSelector>& selector_;
};

} // namespace simplesat
#endif // SRC_CNF_CNF_ENVIRONMENT_STACK_H