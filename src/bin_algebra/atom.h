#ifndef SRC_ATOM_H
#define SRC_ATOM_H

#include "src/bin_algebra/function.h"

namespace tribblesat 
{
class Atom : public Function {
  public:
  Atom(bool t) : Function(NodeType::ATOM), true_(t) { }
  static Atom True();
  static Atom False();
  bool Evaluate(VariableEnvironment env) const override;
  std::set<std::string> GetVariables() const override;
  std::string to_string() const override;

  private:
  bool true_;
};
} // namespace tribblesat
#endif // SRC_ATOM_H