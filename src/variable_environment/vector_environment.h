#ifndef SRC_CNF_CNF_VECTOR_ENVIRONMENT_H
#define SRC_CNF_CNF_VECTOR_ENVIRONMENT_H

#include <vector>
#include "src/variable_environment/variable_environment.h"

namespace tribblesat {
namespace cnf {

class VectorVariableEnvironment : public VariableEnvironment {
  public:
  VectorVariableEnvironment(variable_id count); // Creates an environment with n unbound variables
  VectorVariableEnvironment(variable_id count, VariableState state); // Creates an environment with only variables set to state.

  void assign(variable_id variable, VariableState value) override;
  VariableState lookup(variable_id variable) const override;
  variable_id count() const override { return count_; } 
  variable_id first_unbound() const override;
  std::string to_string() const override;
  
  static VariableState Not(VariableState state);
  private:
  variable_id count_;
  std::vector<VariableState> assignments_;

};

} // namespace cnf
} // namespace tribblesat
#endif // SRC_CNF_CNF_VECTOR_ENVIRONMENT_H