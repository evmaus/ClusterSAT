
#include "src/cnf/cnf_vector_environment.h"
#include <sstream>

namespace tribblesat {
namespace cnf {

VectorVariableEnvironment::VectorVariableEnvironment(variable_id count) : count_(count), assignments_(count+1) {
  for (variable_id i = 1; i <= count_; i++) {
    assign(i, VariableState::SUNBOUND);
  }
}

VectorVariableEnvironment::VectorVariableEnvironment(variable_id count, VariableState state) : count_(count),  assignments_(count+1) { 
  for (variable_id i = 1; i <= count; i++) {
    assign(i, state);
  }
}

void VectorVariableEnvironment::assign(variable_id variable, VariableState value) {
  assignments_[variable] = value;
}

VariableState VectorVariableEnvironment::lookup(variable_id variable) const {
  return assignments_.at(variable);
}

variable_id VectorVariableEnvironment::first_unbound() const {
  for (uint32_t i = 1; i <= count_; i++) {
    if (lookup(i) == VariableState::SUNBOUND) {
      return i;
    }
  }
  return 0;
}

std::string VectorVariableEnvironment::to_string() const {
  std::ostringstream stream;
  stream << "COUNT: " << count_ << " ";
  for (uint32_t i = 1; i <= count_; i++) {
    stream << "{ " << i << " ->" << 
      cnf::VariableEnvironment::StateToString(lookup(i)) << " },";
  }
  return stream.str();
}

} // namespace cnf
} // namespace tribblesat