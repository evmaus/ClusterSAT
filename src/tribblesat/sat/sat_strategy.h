#ifndef SRC_SAT_SAT_STRATEGY_H
#define SRC_SAT_SAT_STRATEGY_H

#include "src/tribblesat/cnf/cnf_and_op.h"
#include "src/tribblesat/cnf/cnf_or_op.h"
#include "src/tribblesat/cnf/cnf_variable.h"
#include "src/tribblesat/variable_environment/variable_environment.h"
namespace tribblesat {
enum SatResultType {
  SAT,
  UNSAT,
  UNKNOWN
};

using SatResult = std::pair<SatResultType, std::vector<int>>;

class SatStrategy {
  public:
  virtual SatResult DetermineCnfSat(cnf::And& term) const = 0;
  virtual ~SatStrategy() {};
};

}
#endif // SRC_SAT_SAT_STRATEGY_H