#ifndef SRC_SAT_SAT_STRATEGY_H
#define SRC_SAT_SAT_STRATEGY_H

#include "src/cnf/cnf_and_op.h"
#include "src/cnf/cnf_or_op.h"
#include "src/cnf/cnf_variable.h"
#include "src/cnf/cnf_variable_environment.h"
namespace tribblesat {
enum SatResultType {
  SAT,
  UNSAT,
  UNKNOWN
};

class SatStrategy {
  public:
  virtual SatResultType DetermineCnfSat(const cnf::And& term) const = 0;
  virtual ~SatStrategy() {};
};

}
#endif // SRC_SAT_SAT_STRATEGY_H