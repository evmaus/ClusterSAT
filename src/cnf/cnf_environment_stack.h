#ifndef SRC_CNF_CNF_ENVIRONMENT_STACK_H
#define SRC_CNF_CNF_ENVIRONMENT_STACK_H

#include <stack>
#include <string>
#include <map>

#include "src/cnf/cnf_variable_environment.h"
#include "src/cnf/cnf_vector_environment.h"

namespace tribblesat {
namespace cnf {

using VariableStackEntry = std::pair<int, VariableState>;

class VariableEnvironmentStack : public VariableEnvironment {
  public:
  VariableEnvironmentStack(variable_id count);
  void push();
  void pop();
  int current_level() const;

  virtual variable_id count() const override;
  void assign(variable_id variable, VariableState value) override;
  VariableState lookup(variable_id variable) const override;
  variable_id first_unbound() const override;
  std::string to_string() const override;
  void Backtrack(int new_level);

  private:
  uint32_t current_depth_ = 0;
  variable_id count_;
  std::map<variable_id, VariableStackEntry> variable_map_;
};

} // namespace cnf
} // namespace tribblesat
#endif // SRC_CNF_CNF_ENVIRONMENT_STACK_H