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

#include "src/simplesat/variable_environment/vector_environment.h"
#include "src/simplesat/variable_environment/linear_variable_selector.h"
#include <sstream>

namespace simplesat {

VectorVariableEnvironment::VectorVariableEnvironment(variable_id count, const VariableSelector& selector) : count_(count), assignments_(count+1), selector_(selector){
  for (variable_id i = 1; i <= count_; i++) {
    assign(i, VariableState::SUNBOUND);
  }
}

VectorVariableEnvironment::VectorVariableEnvironment(variable_id count, VariableState state, const VariableSelector& selector) : count_(count),  assignments_(count+1), selector_(selector) { 
  for (variable_id i = 1; i <= count; i++) {
    assign(i, state);
  }
}

void VectorVariableEnvironment::assign(variable_id variable, VariableState value) {
  assignments_[variable] = value;
}

VariableState VectorVariableEnvironment::lookup(variable_id variable) const {
  return assignments_.at(variable);
}

VariableRecommendation VectorVariableEnvironment::next_unbound() const {
  for (auto it = selector_.cbegin(); it != selector_.cend(); it++) {
    if (lookup(*it) == VariableState::SUNBOUND) {
      return VariableRecommendation(*it, selector_.recommend_assignment(*it));
    }
  }
  return VariableRecommendation(0, VariableState::SUNBOUND);
}

std::string VectorVariableEnvironment::to_string() const {
  std::ostringstream stream;
  stream << "COUNT: " << count_ << " ";
  for (variable_id i = 1; i <= count_; i++) {
    stream << "{ " << i << " ->" << 
      VariableEnvironment::StateToString(lookup(i)) << " },";
  }
  return stream.str();
}

std::vector<int> VectorVariableEnvironment::assignments_by_id() const {
  std::vector<int> result;
  for (variable_id i = 1; i <= count_; i++) {
      switch(lookup(i)) {
        case VariableState::STRUE:
          result.push_back(i);
          break;
        case VariableState::SFALSE:
          result.push_back(-i);
          break;
        case VariableState::SUNBOUND:
          break;
      }
  }
  return result;
}

} // namespace simplesat