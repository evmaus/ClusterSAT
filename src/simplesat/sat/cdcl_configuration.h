#ifndef SRC_SAT_CDCL_CONFIGURATION_H
#define SRC_SAT_CDCL_CONFIGURATION_H

#include "src/simplesat/variable_environment/variable_selector.h"
#include "src/simplesat/sat/compacting_policy.h"
#include "src/simplesat/sat/restart_policy.h"
#include "src/simplesat/cnf/cnf_and_op.h"

namespace simplesat {

class CDCLConfiguration {
  public:
  CDCLConfiguration(uint64_t timeout_ms);
  CDCLConfiguration(uint64_t timeout_ms, 
  VariableSelectorType selector, 
  CompactingPolicyType policy,
  RestartPolicyType restart);

  std::unique_ptr<VariableSelector> AllocateNewVariableSelector(const cnf::And& term) const;
  std::unique_ptr<CompactingPolicy> AllocateNewCompactingPolicy(const cnf::And& term) const;
  std::unique_ptr<RestartPolicy> AllocateNewRestartPolicy(const cnf::And& term) const;
  uint64_t timeout_ms() const { return timeout_ms_; }

  private:
  uint64_t timeout_ms_;
  VariableSelectorType selector_type_;
  CompactingPolicyType compacting_policy_;
  RestartPolicyType restart_policy_;
};

} // namespace simplesat

#endif // SRC_SAT_CDCL_CONFIGURATION_H