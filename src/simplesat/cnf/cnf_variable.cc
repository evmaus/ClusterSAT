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

#include "src/simplesat/cnf/cnf_variable.h"

#include <string>

namespace simplesat {
namespace cnf {

Variable::Variable(variable_id variable) : variable_(variable), negated_(false) {

}

Variable::Variable(variable_id variable, bool negated) 
  : variable_(variable), negated_(negated)
{ }

VariableState Variable::GetValueInEnvironment(const VariableEnvironment& env) const {
  if (negated_) {
    return VariableEnvironment::Not(env.lookup(variable_));
  } 
  else {
    return env.lookup(variable_);
  }
}

std::string Variable::to_string() const {
  if (negated_) {
    return "!x_" + std::to_string(variable_);
  }

  return "x_" + std::to_string(variable_);
}

} // namespace cnf
} // namespace simplesat