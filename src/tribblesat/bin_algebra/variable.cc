#include "src/tribblesat/bin_algebra/variable.h"

namespace tribblesat {

namespace binary {
Variable::Variable(std::string name) 
  : Function(NodeType::VARIABLE), 
  name_(name) 
{ }

bool Variable::Evaluate(VariableEnvironment env) const {
  // TODO: Handle unassigned variable.
  return env.Lookup(name_);
}

std::set<std::string> Variable::GetVariables() const {
  std::set<std::string> variable;
  variable.insert(name_);
  return variable;
}

std::string Variable::to_string() const {
  return "v:" + name_;
}
} // namespace binary
} // namespace tribblesat