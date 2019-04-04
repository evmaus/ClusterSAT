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

#ifndef SRC_VARIABLE_ENVIRONMENT_H
#define SRC_VARIABLE_ENVIRONMENT_H

#include <map>
#include <string>

namespace simplesat {
namespace binary {
class VariableEnvironment {
  public:
  static VariableEnvironment Empty();

  bool Lookup(::std::string variable_name);
  void Assign(::std::string variable_name, bool value);
  
  ::std::map<std::string, bool>::iterator begin() { return variables_.begin(); }
  ::std::map<std::string, bool>::iterator end() { return variables_.end(); }

  private:
  VariableEnvironment();
  ::std::map<std::string, bool> variables_;
};
} // namespace binary
} // namespace simplesat

#endif // SRC_VARIABLE_ENVIRONMENT_H