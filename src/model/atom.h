#ifndef SRC_ATOM_H
#define SRC_ATOM_H

#include "src/model/function.h"

namespace tribblesat 
{
class Atom : public Function {
  public:
  static Atom True();
  static Atom False();
  bool Evaluate(VariableEnvironment env) const override;
  std::vector<std::string> GetUnboundVariables() const override;
  private:
  Atom(bool t) : Function(NodeType::ATOM), true_(t) { }
  bool true_;
};
} // namespace tribblesat
#endif // SRC_ATOM_H