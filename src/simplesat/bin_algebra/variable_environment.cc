#include "src/simplesat/bin_algebra/variable_environment.h"

#include <string>

namespace simplesat {
namespace binary {

VariableEnvironment VariableEnvironment::Empty() 
{ 
  return VariableEnvironment();
}

VariableEnvironment::VariableEnvironment() {

}

bool VariableEnvironment::Lookup(std::string variable_name) {
    return variables_[variable_name];
}

void VariableEnvironment::Assign(std::string variable_name, bool value) {
    variables_[variable_name] = value;
}
} // namespace binary
} // namespace simplesat