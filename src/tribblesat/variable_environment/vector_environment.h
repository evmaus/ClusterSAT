#ifndef SRC_CNF_CNF_VECTOR_ENVIRONMENT_H
#define SRC_CNF_CNF_VECTOR_ENVIRONMENT_H

#include <vector>
#include "src/tribblesat/variable_environment/variable_environment.h"
#include "src/tribblesat/variable_environment/variable_selector.h"

namespace tribblesat {

class VectorVariableEnvironment : public VariableEnvironment {
  public:
  
  VectorVariableEnvironment(variable_id count, VariableState state); // Creates an environment with only variables set to state.
  VectorVariableEnvironment(variable_id count, const VariableSelector& selector); // Creates an environment with n unbound variables
  VectorVariableEnvironment(variable_id count, VariableState state, const VariableSelector& selector); // Creates an environment with only variables set to state.

  void assign(variable_id variable, VariableState value) override;
  VariableState lookup(variable_id variable) const override;
  variable_id count() const override { return count_; } 
  VariableRecommendation next_unbound() const override;
  std::string to_string() const override;
  
  std::vector<int> assignments_by_id() const override;

  static VariableState Not(VariableState state);
  private:
  variable_id count_;
  std::vector<VariableState> assignments_;
  const VariableSelector& selector_;
};

} // namespace tribblesat
#endif // SRC_CNF_CNF_VECTOR_ENVIRONMENT_H