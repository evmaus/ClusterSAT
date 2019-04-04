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

#ifndef SRC_BINARY_OP_H
#define SRC_BINARY_OP_H

#include "src/simplesat/bin_algebra/function.h"

namespace simplesat 
{
namespace binary {
enum BinaryType {
    AND,
    OR,
    XOR,
    IMPLIES,
    IFF
};

class BinaryOp : public Function {
  public:
  static BinaryOp And(Function& lhs, Function& rhs);
  static BinaryOp Or(Function& lhs, Function& rhs);
  static BinaryOp Xor(Function& lhs, Function& rhs);
  static BinaryOp Implies(Function& lhs, Function& rhs);
  static BinaryOp IFF(Function& lhs, Function& rhs);

  BinaryOp(BinaryType type, const Function& lhs, const Function& rhs);
  
  bool Evaluate(VariableEnvironment env) const override;
  std::set<std::string> GetVariables() const override;
  std::string to_string() const override;

  private:
  BinaryType op_type_;
  const Function& lhs_;
  const Function& rhs_;
};
} // namespace binary
} // namespace simplesat
#endif // SRC_BINARY_OP_H