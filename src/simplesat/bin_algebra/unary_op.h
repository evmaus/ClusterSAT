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


