#include "src/simplesat/cnf/cnf_variable.h"

#include <string>

namespace simplesat {
namespace cnf {

Variable::Variable(variable_id variable) : variable_(variable), negated_(false) {

}

Variable::Variable(variable_id variable, bool negated) 
  : variable_(variable), negated_(negated)
{ }

VariableState Variable::GetValueInEnvironment(const VariableEnvironment& env) const {
  if (negated_) {
    return VariableEnvironment::Not(env.lookup(variable_));
  } 
  else {
    return env.lookup(variable_);
  }
}

std::string Variable::to_string() const {
  if (negated_) {
    return "!x_" + std::to_string(variable_);
  }

  return "x_" + std::to_string(variable_);
}

} // namespace cnf
} // namespace simplesat