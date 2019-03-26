#ifndef SRC_VARIABLE_ENVIRONMENT_LINEAR_VARIABLE_SELECTOR_H
#define SRC_VARIABLE_ENVIRONMENT_LINEAR_VARIABLE_SELECTOR_H

#include "src/simplesat/variable_environment/variable_environment.h"
#include "src/simplesat/variable_environment/variable_selector.h"

namespace simplesat {

class LinearVariableSelector : public VariableSelector {
  public:
  LinearVariableSelector(variable_id max_id);
  VariableIterator cbegin() const override;
  VariableIterator cend() const override;
  
  VariableState recommend_assignment(variable_id id) const override { return VariableState::SFALSE; }

  // Do nothing to recalculate for linear selection.
  void recalculate(const cnf::Or& learned_term) override 
  { };
  private:
  std::vector<variable_id> order_;
};

} // namespace simplesat
#endif // SRC_VARIABLE_ENVIRONMENT_LINEAR_VARIABLE_SELECTOR_H