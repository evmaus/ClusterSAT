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


#include "src/simplesat/variable_environment/variable_environment.h"

#include <cstdlib>
#include <string>

namespace simplesat {

VariableState VariableEnvironment::Not(VariableState state) {
  switch(state)
  {
    case VariableState::STRUE:
      return VariableState::SFALSE;
    case VariableState::SFALSE:
      return VariableState::STRUE;
    default:
      return VariableState::SUNBOUND;
  }
}

VariableState VariableEnvironment::RandomState() {
  int random = rand();
  if (random % 2 == 0) {
    return VariableState::STRUE;
  } else {
    return VariableState::SFALSE;
  }
}

std::string VariableEnvironment::StateToString(VariableState state) {
  switch(state)
  {
    case VariableState::STRUE:
      return "TRUE";
    case VariableState::SFALSE:
      return "FALSE";
    case VariableState::SUNBOUND:
      return "UNBOUND";
  }
}

} // namespace simplesat