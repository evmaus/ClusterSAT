#include "src/tribblesat/variable_environment/linear_variable_selector.h"

namespace tribblesat {

LinearVariableSelector::LinearVariableSelector(variable_id max_id) 
{
  order_.clear();
  order_.reserve(max_id);
  for (int i = 1; i <= max_id; i++) {
    order_.push_back(i);
  }
}

VariableIterator LinearVariableSelector::cbegin() const {
  return order_.cbegin();
}

VariableIterator LinearVariableSelector::cend() const {
  return order_.cend();
}

} // namespace tribblesat