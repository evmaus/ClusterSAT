#include "src/tribblesat/variable_environment/vector_environment.h"
#include "src/tribblesat/variable_environment/linear_variable_selector.h"
#include <sstream>

namespace tribblesat {

VectorVariableEnvironment::VectorVariableEnvironment(variable_id count, const VariableSelector& selector) : count_(count), assignments_(count+1), selector_(selector){
  for (variable_id i = 1; i <= count_; i++) {
    assign(i, VariableState::SUNBOUND);
  }
}

VectorVariableEnvironment::VectorVariableEnvironment(variable_id count, VariableState state, const VariableSelector& selector) : count_(count),  assignments_(count+1), selector_(selector) { 
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

VariableRecommendation VectorVariableEnvironment::next_unbound() const {
  for (auto it = selector_.cbegin(); it != selector_.cend(); it++) {
    if (lookup(*it) == VariableState::SUNBOUND) {
      return VariableRecommendation(*it, selector_.recommend_assignment(*it));
    }
  }
  return VariableRecommendation(0, VariableState::SUNBOUND);
}

std::string VectorVariableEnvironment::to_string() const {
  std::ostringstream stream;
  stream << "COUNT: " << count_ << " ";
  for (variable_id i = 1; i <= count_; i++) {
    stream << "{ " << i << " ->" << 
      VariableEnvironment::StateToString(lookup(i)) << " },";
  }
  return stream.str();
}

std::vector<int> VectorVariableEnvironment::assignments_by_id() const {
  std::vector<int> result;
  for (variable_id i = 1; i <= count_; i++) {
      switch(lookup(i)) {
        case VariableState::STRUE:
          result.push_back(i);
          break;
        case VariableState::SFALSE:
          result.push_back(-i);
          break;
        case VariableState::SUNBOUND:
          break;
      }
  }
  return result;
}

} // namespace tribblesat