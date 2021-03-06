// Copyright 2019 Google LLC
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "src/simplesat/sat/cdcl_configuration.h"

#include "absl/memory/memory.h"
#include "src/simplesat/variable_environment/linear_variable_selector.h"
#include "src/simplesat/variable_environment/vsids_variable_selector.h"

namespace simplesat {

CDCLConfiguration::CDCLConfiguration(uint64_t timeout_ms)
  : timeout_ms_(timeout_ms), 
  selector_type_(VariableSelectorType::LINEAR), 
  compacting_policy_(CompactingPolicyType::NONE),
  restart_policy_(RestartPolicyType::NONE)
{

}

CDCLConfiguration::CDCLConfiguration(uint64_t timeout_ms, 
  VariableSelectorType selector, 
  CompactingPolicyType policy,
  RestartPolicyType restart)
  : timeout_ms_(timeout_ms), selector_type_(selector), compacting_policy_(policy), restart_policy_(restart)
{
  
}

std::unique_ptr<VariableSelector> CDCLConfiguration::AllocateNewVariableSelector(const cnf::And& term) const
{
  switch(selector_type_) {
    case VariableSelectorType::LINEAR:
      return absl::make_unique<LinearVariableSelector>(term.variable_count());
    case VariableSelectorType::VSIDS:
      return absl::make_unique<VSIDSVariableSelector>(term, 0.5, 50);
  }
}

std::unique_ptr<CompactingPolicy> CDCLConfiguration::AllocateNewCompactingPolicy(const cnf::And& term) const
{
  switch(compacting_policy_) {
    case CompactingPolicyType::NONE:
      return absl::make_unique<KeepAllCompactingPolicy>();
    case CompactingPolicyType::TERM_SIZE:
      return absl::make_unique<TermSizeCompactingPolicy>(0, 4, 5);
  }
}

std::unique_ptr<RestartPolicy> CDCLConfiguration::AllocateNewRestartPolicy(const cnf::And& term) const {
  switch(restart_policy_) {
    case RestartPolicyType::NONE:
      return absl::make_unique<NoRestartPolicy>();
    case RestartPolicyType::GEOMETRIC:
      return absl::make_unique<GeometricRestartPolicy>(1.5, 100);
  }
}

} // namespace simplesat