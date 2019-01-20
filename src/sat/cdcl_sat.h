#ifndef SRC_SAT_CDCL_SAT_H
#define SRC_SAT_CDCL_SAT_H

#include "src/sat/sat_strategy.h"
#include "src/cnf/cnf_and_op.h"
#include "src/cnf/cnf_or_op.h"
#include "src/cnf/cnf_variable.h"
#include "src/sat/cdcl_configuration.h"

namespace tribblesat {

class CDCLSatStrategy : public SatStrategy {
  public:
  CDCLSatStrategy(CDCLConfiguration configuration);  // Handle timeout parameter...
  SatResult DetermineCnfSat(cnf::And& term) const override;

  private:
  SatResult DetermineCnfSatInternal(
    cnf::And& term, std::atomic_bool& run) const;
  CDCLConfiguration config_;
};

} // tribblesat

#endif // SRC_SAT_CDCL_SAT_H