#include "src/tribblesat/bin_algebra/atom.h"

namespace tribblesat {
namespace binary {

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

std::set<std::string> Atom::GetVariables() const {
  return std::set<std::string>();
}

std::string Atom::to_string() const {
  if(true_) {
    return "true";
  } else {
    return "false";
  }
}

} // namespace binary
} // namespace tribblesat