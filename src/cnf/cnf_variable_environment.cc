
#include "src/cnf/cnf_variable_environment.h"

#include <cstdlib>
#include <string>

namespace tribblesat {
namespace cnf {

VariableState VariableEnvironment::Not(VariableState state) {
  switch(state)
  {
    case VariableState::STRUE:
      return VariableState::SFALSE;
    case VariableState::SFALSE:
      return VariableState::STRUE;
    default:
      return VariableState::SUNBOUND;
  }
}

VariableState VariableEnvironment::RandomState() {
  int random = rand();
  /*if (random % 2 == 0) {
    return VariableState::STRUE;
  } else {
    return VariableState::SFALSE;
  }*/
  return VariableState::STRUE;
}

std::string VariableEnvironment::StateToString(VariableState state) {
  switch(state)
  {
    case VariableState::STRUE:
      return "TRUE";
    case VariableState::SFALSE:
      return "FALSE";
    case VariableState::SUNBOUND:
      return "UNBOUND";
  }
}

} // namespace cnf
} // namespace tribblesat