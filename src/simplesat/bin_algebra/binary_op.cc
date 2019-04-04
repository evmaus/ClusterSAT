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

#include "src/simplesat/bin_algebra/binary_op.h"

#include <iostream>

namespace simplesat {
namespace binary {

BinaryOp::BinaryOp(BinaryType type, const Function& lhs, const Function& rhs) 
    : Function(NodeType::OP),
    op_type_(type), lhs_(lhs), rhs_(rhs) 
  {}

BinaryOp BinaryOp::And(Function& lhs, Function& rhs)
{
  return BinaryOp(BinaryType::AND, lhs, rhs);
}

BinaryOp BinaryOp::Or(Function& lhs, Function& rhs)
{
  return BinaryOp(BinaryType::OR, lhs, rhs);
}

BinaryOp BinaryOp::Xor(Function& lhs, Function& rhs)
{
  return BinaryOp(BinaryType::XOR, lhs, rhs);
}

BinaryOp BinaryOp::Implies(Function& lhs, Function& rhs)
{
  return BinaryOp(BinaryType::IMPLIES, lhs, rhs);
}

BinaryOp BinaryOp::IFF(Function& lhs, Function& rhs)
{
  return BinaryOp(BinaryType::IFF, lhs, rhs);
}


bool BinaryOp::Evaluate(VariableEnvironment env) const
{

  bool lhs = lhs_.Evaluate(env);
  bool rhs = rhs_.Evaluate(env);
  switch(op_type_)
  {
      case BinaryType::XOR:
        return lhs ? !rhs : rhs;
      case BinaryType::AND:
        return (lhs && rhs);
      case BinaryType::OR:
        return (lhs || rhs);
      case BinaryType::IMPLIES:
        return lhs ? rhs : true;
      case BinaryType::IFF:
        return lhs == rhs;
  }
}

std::set<std::string> BinaryOp::GetVariables() const {
  auto lhs = lhs_.GetVariables();
  auto rhs = rhs_.GetVariables();
  for (auto it = rhs.begin(); it != rhs.end(); it++){
    lhs.insert(*it);
  }
  return lhs;
}

std::string BinaryOp::to_string() const {
  std::string lhs = lhs_.to_string();
  std::string rhs = rhs_.to_string();
  switch(op_type_) {
    case BinaryType::XOR:
      return "(" + lhs + " ^ " + rhs + ")";
    case BinaryType::AND:
      return "(" + lhs + " & " + rhs + ")";
    case BinaryType::OR:
      return "(" + lhs +  " | " + rhs + ")";
    case BinaryType::IMPLIES:
      return "(" + lhs + " -> " + rhs + ")";
    case BinaryType::IFF:
      return "(" + lhs + " <-> " + rhs + ")";
  }
}

} // namespace binary
} // namespace simplesat
