#ifndef SRC_BINARY_OP_H
#define SRC_BINARY_OP_H

#include "src/model/function.h"

namespace tribblesat 
{
enum BinaryType {
    AND,
    OR,
    XOR
};
class BinaryOp : public Function {
  public:
  static BinaryOp And(Function& lhs, Function& rhs);
  static BinaryOp Or(Function& lhs, Function& rhs);
  static BinaryOp Xor(Function& lhs, Function& rhs);

  BinaryOp(BinaryType type, const Function& lhs, const Function& rhs);
  
  bool Evaluate(VariableEnvironment env) const override;
  std::vector<std::string> GetUnboundVariables() const override;

  private:
  BinaryType op_type_;
  const Function& lhs_;
  const Function& rhs_;
};
} // namespace tribblesat
#endif // SRC_BINARY_OP_H