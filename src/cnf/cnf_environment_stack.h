#ifndef SRC_CNF_CNF_ENVIRONMENT_STACK_H
#define SRC_CNF_CNF_ENVIRONMENT_STACK_H

#include <stack>
#include <string>

#include "src/cnf/cnf_variable_environment.h"
#include "src/cnf/cnf_vector_environment.h"

namespace tribblesat {
namespace cnf {

class VariableEnvironmentStack : public VariableEnvironment {
  public:
  VariableEnvironmentStack(VectorVariableEnvironment env);
  void push();
  void pop();
  int current_level() const;

  virtual variable_id count() const override;
  void assign(variable_id variable, VariableState value) override;
  VariableState lookup(variable_id variable) const override;
  variable_id first_unbound() const override;
  std::string to_string() const override;

  private:
  std::stack<VectorVariableEnvironment> variable_stack_;

};

} // namespace cnf
} // namespace tribblesat
#endif // SRC_CNF_CNF_ENVIRONMENT_STACK_H