#ifndef SRC_SAT_CDCL_CONFIGURATION_H
#define SRC_SAT_CDCL_CONFIGURATION_H

#include "src/variable_environment/variable_selector.h"
#include "src/cnf/cnf_and_op.h"

namespace tribblesat {

class CDCLConfiguration {
  public:
  CDCLConfiguration(uint64_t timeout_ms);
  CDCLConfiguration(uint64_t timeout_ms, VariableSelectorType selector);

  std::unique_ptr<VariableSelector> AllocateNewVariableSelector(const cnf::And& term) const;

  uint64_t timeout_ms() const { return timeout_ms_; }

  private:
  uint64_t timeout_ms_;
  VariableSelectorType selector_type_;
};

} // namespace tribblesat

#endif // SRC_SAT_CDCL_CONFIGURATION_H