#ifndef SRC_SAT_SAT_STRATEGY_H
#define SRC_SAT_SAT_STRATEGY_H

#include "src/model/function.h"

namespace tribblesat {
enum SatResultType {
  SAT,
  UNSAT,
  UNKNOWN
};

class SatStrategy {
  public:
  virtual SatResultType DetermineSat(const Function& function) const = 0;
  virtual ~SatStrategy() {};
};

}
#endif // SRC_SAT_SAT_STRATEGY_H