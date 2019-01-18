#include "src/cnf/cnf_environment_stack.h"

#include <stack>
#include <string>

#include "src/cnf/cnf_vector_environment.h"

namespace tribblesat {
namespace cnf {

VariableEnvironmentStack::VariableEnvironmentStack(VectorVariableEnvironment env) {
  variable_stack_.push(env);
}

void VariableEnvironmentStack::push() {
  VectorVariableEnvironment env = variable_stack_.top();
  variable_stack_.push(env);
}

void VariableEnvironmentStack::pop() {
  variable_stack_.pop();
}

int VariableEnvironmentStack::current_level() const {
  return variable_stack_.size();
}

variable_id VariableEnvironmentStack::count() const {
  return variable_stack_.top().count();
}

void VariableEnvironmentStack::assign(variable_id variable, VariableState value) {
  variable_stack_.top().assign(variable, value);
}

VariableState VariableEnvironmentStack::lookup(variable_id variable) const {
  return variable_stack_.top().lookup(variable);
}

variable_id VariableEnvironmentStack::first_unbound() const {
  return variable_stack_.top().first_unbound();
}

std::string VariableEnvironmentStack::to_string() const {
  return variable_stack_.top().to_string();
}

} // namespace cnf
} // namespace tribblesat