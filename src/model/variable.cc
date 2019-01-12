#include "src/model/variable.h"

namespace tribblesat {

Variable::Variable(std::string name) 
  : Function(NodeType::VARIABLE), 
  name_(name) 
{ }

bool Variable::Evaluate(VariableEnvironment env) const {
  // TODO: Handle unassigned variable.
  return env.Lookup(name_);
}

std::vector<std::string> Variable::GetUnboundVariables() const {
  std::vector<std::string> variable;
  variable.push_back(name_);
  return variable;
}
} // namespace tribblesat