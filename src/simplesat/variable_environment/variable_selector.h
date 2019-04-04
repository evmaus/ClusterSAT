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

#ifndef SRC_CNF_VARIABLE_SELECTOR_H
#define SRC_CNF_VARIABLE_SELECTOR_H

#include <vector>
#include "src/simplesat/variable_environment/variable_environment.h"
#include "src/simplesat/cnf/cnf_and_op.h"
#include "src/simplesat/common/stats.h"

namespace simplesat { 

using VariableIterator = std::vector<variable_id>::const_iterator;

enum class VariableSelectorType {
  LINEAR,
  VSIDS,
};

// A variable selector is a ranking of variables to assign to.
// It's used by various variable environments to change how they choose the next unassigned variable.
class VariableSelector {
  public:
  virtual ~VariableSelector() { };
  virtual VariableIterator cbegin() const = 0;
  virtual VariableIterator cend() const = 0;
  virtual VariableState recommend_assignment(variable_id id) const = 0;
  virtual void recalculate(const cnf::Or& learned_term) = 0;
};

} // namespace simplesat
#endif // SRC_VARIABLE_SELECTION_VARIABLE_SELECTOR_H