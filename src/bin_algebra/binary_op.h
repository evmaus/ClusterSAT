#ifndef SRC_BINARY_OP_H
#define SRC_BINARY_OP_H

#include "src/bin_algebra/function.h"

namespace tribblesat 
{
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
} // namespace tribblesat
#endif // SRC_BINARY_OP_H