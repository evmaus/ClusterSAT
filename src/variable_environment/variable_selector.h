#ifndef SRC_CNF_VARIABLE_SELECTOR_H
#define SRC_CNF_VARIABLE_SELECTOR_H

#include <vector>
#include "src/variable_environment/variable_environment.h"

namespace tribblesat { 

// A variable selector is a ranking of variables to assign to.
// It's used by various variable environments to change how they choose the next unassigned variable.

class VariableSelector {
  virtual ~VariableSelector() { };
  virtual std::vector<variable_id>::const_iterator cbegin() = 0;
  virtual std::vector<variable_id>::const_iterator cend() = 0;
};

} // namespace tribblesat
#endif // SRC_VARIABLE_SELECTION_VARIABLE_SELECTOR_H