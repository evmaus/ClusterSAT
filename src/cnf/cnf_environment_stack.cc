#include "src/cnf/cnf_environment_stack.h"

#include <stack>
#include <string>
#include <sstream>

#include "src/cnf/cnf_vector_environment.h"
#include "src/common/log.h"

namespace tribblesat {
namespace cnf {

VariableEnvironmentStack::VariableEnvironmentStack(variable_id count) : count_(count) {
  for (variable_id id = 0; id <= count_; id++) {
    variable_map_[id] = VariableStackEntry(0, VariableState::SUNBOUND);
  }
}

void VariableEnvironmentStack::push() {
  current_depth_++;
}

void VariableEnvironmentStack::pop() {
  Backtrack(current_depth_-1);
}

void VariableEnvironmentStack::Backtrack(int new_level) {
  for (variable_id id = 0; id <= count_; id++) {
    VariableStackEntry lookup = variable_map_.at(id);
    if (lookup.first > new_level) {
      variable_map_[id] = VariableStackEntry(0, VariableState::SUNBOUND);
    }
  }
  current_depth_ = new_level;
}

int VariableEnvironmentStack::current_level() const {
  return current_depth_;
}

variable_id VariableEnvironmentStack::count() const {
  return count_;
}

void VariableEnvironmentStack::assign(variable_id variable, VariableState value) {
  variable_map_[variable] = VariableStackEntry(current_depth_, value);
}

VariableState VariableEnvironmentStack::lookup(variable_id variable) const {
  if (variable == 0 || variable > count_) {
    LOG(LogLevel::ERROR, "Attempted to look up variable id " + std::to_string(variable) + " in env of count "+std::to_string(count_));
  }

  VariableStackEntry lookup = variable_map_.at(variable);
  if (lookup.first <= current_depth_) {
    return lookup.second;
  } else {
    return VariableState::SUNBOUND;
  }
}

variable_id VariableEnvironmentStack::first_unbound() const {
  for (variable_id id = 1; id <= count_; id++) {
    if (lookup(id) == VariableState::SUNBOUND) {
      return id;
    }
  }
  return 0;
}

std::string VariableEnvironmentStack::to_string() const {
  std::ostringstream stream;
  stream << "COUNT: " << count_ << " ";
  for (variable_id i = 1; i <= count_; i++) {
    stream << "{ " << i << " ->" << 
      cnf::VariableEnvironment::StateToString(lookup(i)) << " },";
  }
  return stream.str();
}

} // namespace cnf
} // namespace tribblesat