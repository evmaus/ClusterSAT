#ifndef SRC_CNF_CNF_ENVIRONMENT_STACK_H
#define SRC_CNF_CNF_ENVIRONMENT_STACK_H

#include <stack>
#include <string>
#include <map>

#include "src/tribblesat/variable_environment/variable_environment.h"
#include "src/tribblesat/variable_environment/variable_selector.h"

namespace tribblesat {

using VariableStackEntry = std::pair<int, VariableState>;

class VariableEnvironmentStack : public VariableEnvironment {
  public:
  VariableEnvironmentStack(variable_id count, const std::unique_ptr<VariableSelector>& selector);
  virtual void push();
  virtual void pop();
  virtual int current_level() const;

  virtual variable_id count() const override;
  virtual void assign(variable_id variable, VariableState value) override;
  virtual VariableState lookup(variable_id variable) const override;
  virtual VariableRecommendation next_unbound() const override;
  virtual std::string to_string() const override;
  virtual void Backtrack(int new_level);
  virtual std::vector<int> assignments_by_id() const override;
  private:
  uint32_t current_depth_ = 0;
  variable_id count_;
  std::map<variable_id, VariableStackEntry> variable_map_;
  const std::unique_ptr<VariableSelector>& selector_;
};

} // namespace tribblesat
#endif // SRC_CNF_CNF_ENVIRONMENT_STACK_H