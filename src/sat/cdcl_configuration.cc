#include "src/sat/cdcl_configuration.h"

#include "absl/memory/memory.h"
#include "src/variable_environment/linear_variable_selector.h"
#include "src/variable_environment/vsids_variable_selector.h"

namespace tribblesat {

CDCLConfiguration::CDCLConfiguration(uint64_t timeout_ms)
  : timeout_ms_(timeout_ms), selector_type_(VariableSelectorType::LINEAR) 
{

}

CDCLConfiguration::CDCLConfiguration(uint64_t timeout_ms, VariableSelectorType selector)
  : timeout_ms_(timeout_ms), selector_type_(selector) 
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

} // namespace tribblesat