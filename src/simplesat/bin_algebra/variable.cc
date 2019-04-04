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

#include "src/simplesat/bin_algebra/variable.h"

namespace simplesat {

namespace binary {
Variable::Variable(std::string name) 
  : Function(NodeType::VARIABLE), 
  name_(name) 
{ }

bool Variable::Evaluate(VariableEnvironment env) const {
  // TODO: Handle unassigned variable.
  return env.Lookup(name_);
}

std::set<std::string> Variable::GetVariables() const {
  std::set<std::string> variable;
  variable.insert(name_);
  return variable;
}

std::string Variable::to_string() const {
  return "v:" + name_;
}
} // namespace binary
} // namespace simplesat