#include "src/model/atom.h"

namespace tribblesat
{
Atom Atom::True()
{
  return Atom(true);
}
Atom Atom::False()
{
  return Atom(false);
}
bool Atom::Evaluate(VariableEnvironment env) const
{
  return true_;
}

std::vector<std::string> Atom::GetUnboundVariables() const {
  return std::vector<std::string>();
}
} // namespace tribblesat