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

#ifndef SRC_CNF_CNF_VARIABLE_ENVIRONMENT_H
#define SRC_CNF_CNF_VARIABLE_ENVIRONMENT_H

#include <vector>

namespace simplesat {
typedef int64_t variable_id;

enum VariableState {
  STRUE,
  SFALSE,
  SUNBOUND
};

using VariableRecommendation = std::pair<variable_id, VariableState>;

class VariableEnvironment {
  public:
  virtual ~VariableEnvironment() {};

  virtual void assign(variable_id variable, VariableState value) = 0;
  virtual VariableState lookup(variable_id variable) const = 0;
  virtual variable_id count() const = 0;
  virtual VariableRecommendation next_unbound() const = 0;
  virtual std::string to_string() const = 0;

  static VariableState Not(VariableState state);
  static VariableState RandomState();
  static std::string StateToString(VariableState state);

  virtual std::vector<int> assignments_by_id() const = 0;
  
};

} // namespace simplesat
#endif // SRC_CNF_CNF_VARIABLE_ENVIRONMENT_H