#ifndef SRC_UNARY_OP_H
#define SRC_UNARY_OP_H

#include "src/model/function.h"

namespace tribblesat 
{
enum UnaryType {
    NOT,
    NOP
};
class UnaryOp : public Function {
  public:
  static UnaryOp Not(Function& inner);
  static UnaryOp Nop(Function& inner);
  bool Evaluate(VariableEnvironment env) const override;
  std::vector<std::string> GetUnboundVariables() const override;
  
  private:
  UnaryOp(UnaryType type, const Function& inner);
  UnaryType op_type_;
  const Function& inner_;
};
} // namespace tribblesat
#endif // SRC_UNARY_OP_H


