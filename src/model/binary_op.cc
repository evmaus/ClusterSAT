#include "src/model/binary_op.h"

#include <iostream>

namespace tribblesat {

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

bool BinaryOp::Evaluate(VariableEnvironment env) const
{
  switch(op_type_)
  {
      case BinaryType::XOR:
      {
        bool lhs = lhs_.Evaluate(env);
        bool rhs = rhs_.Evaluate(env);
        return lhs ? !rhs : rhs;
      }
      case BinaryType::AND:
      {
        bool lhs = lhs_.Evaluate(env);
        bool rhs = rhs_.Evaluate(env);
        return (lhs && rhs);
      }
      case BinaryType::OR:
      {
        bool lhs = lhs_.Evaluate(env);
        bool rhs = rhs_.Evaluate(env);
        return (lhs || rhs);
      }
  }
}


std::vector<std::string> BinaryOp::GetUnboundVariables() const {
  auto lhs = lhs_.GetUnboundVariables();
  auto rhs = rhs_.GetUnboundVariables();
  lhs.insert(lhs.end(), rhs.begin(), rhs.end());
  return lhs;
}

} // namespace tribblesat
