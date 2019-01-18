#include "src/variable_environment/environment_stack.h"

#include <stack>
#include <string>
#include <sstream>

#include "src/common/log.h"

namespace tribblesat {

VariableEnvironmentStack::VariableEnvironmentStack(variable_id count, const std::unique_ptr<VariableSelector>& selector) : count_(count), selector_(selector) {
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

VariableRecommendation VariableEnvironmentStack::next_unbound() const {
  for (auto it = selector_->cbegin(); it != selector_->cend(); it++) {
    if (lookup(*it) == VariableState::SUNBOUND) {
      return VariableRecommendation(*it, selector_->recommend_assignment(*it));
    }
  }
  return VariableRecommendation(0, VariableState::SUNBOUND);
}

std::string VariableEnvironmentStack::to_string() const {
  std::ostringstream stream;
  stream << "COUNT: " << count_ << " ";
  for (variable_id i = 1; i <= count_; i++) {
    stream << "{ " << i << " ->" << 
      VariableEnvironment::StateToString(lookup(i)) << " },";
  }
  return stream.str();
}

} // namespace tribblesat