#ifndef SRC_CNF_VARIABLE_SELECTOR_H
#define SRC_CNF_VARIABLE_SELECTOR_H

#include <vector>
#include "src/tribblesat/variable_environment/variable_environment.h"
#include "src/tribblesat/cnf/cnf_and_op.h"
#include "src/tribblesat/common/stats.h"

namespace tribblesat { 

using VariableIterator = std::vector<variable_id>::const_iterator;

enum class VariableSelectorType {
  LINEAR,
  VSIDS,
};

// A variable selector is a ranking of variables to assign to.
// It's used by various variable environments to change how they choose the next unassigned variable.
class VariableSelector {
  public:
  virtual ~VariableSelector() { };
  virtual VariableIterator cbegin() const = 0;
  virtual VariableIterator cend() const = 0;
  virtual VariableState recommend_assignment(variable_id id) const = 0;
  virtual void recalculate(const cnf::Or& learned_term) = 0;
};

} // namespace tribblesat
#endif // SRC_VARIABLE_SELECTION_VARIABLE_SELECTOR_H