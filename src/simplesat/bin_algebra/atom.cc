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

#include "src/simplesat/bin_algebra/atom.h"

namespace simplesat {
namespace binary {

Atom Atom::True()
{
  return Atom(true);
}

Atom Atom::False()
{
  return Atom(false);
}

bool Atom::Evaluate(VariableEnvironment env) const
{
  return true_;
}

std::set<std::string> Atom::GetVariables() const {
  return std::set<std::string>();
}

std::string Atom::to_string() const {
  if(true_) {
    return "true";
  } else {
    return "false";
  }
}

} // namespace binary
} // namespace simplesat