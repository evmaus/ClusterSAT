/*
 * Copyright 2019 Google LLC
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

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