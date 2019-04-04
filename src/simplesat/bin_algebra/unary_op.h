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

#ifndef SRC_UNARY_OP_H
#define SRC_UNARY_OP_H

#include "src/simplesat/bin_algebra/function.h"

namespace simplesat 
{
namespace binary {
enum UnaryType {
    NOT,
    NOP
};
class UnaryOp : public Function {
  public:
  static UnaryOp Not(Function& inner);
  static UnaryOp Nop(Function& inner);
  UnaryOp(UnaryType type, const Function& inner);
  
  std::string to_string() const override;
  bool Evaluate(VariableEnvironment env) const override;
  std::set<std::string> GetVariables() const override;
  
  private:
  UnaryType op_type_;
  const Function& inner_;
};
} // namespace binary
} // namespace simplesat
#endif // SRC_UNARY_OP_H


