#ifndef SRC_SAT_CDCL_SAT_H
#define SRC_SAT_CDCL_SAT_H

#include "src/tribblesat/sat/sat_strategy.h"
#include "src/tribblesat/cnf/cnf_and_op.h"
#include "src/tribblesat/cnf/cnf_or_op.h"
#include "src/tribblesat/cnf/cnf_variable.h"
#include "src/tribblesat/sat/cdcl_configuration.h"

namespace tribblesat {

class CDCLSatStrategy : public SatStrategy {
  public:
  CDCLSatStrategy(CDCLConfiguration configuration);  // Handle timeout parameter...
  
  // Determine SAT with a timeout
  SatResult DetermineCnfSat(cnf::And& term) const override;

  // Determine SAT with a cancellation boolean.
  SatResult DetermineCnfSatWithCancellation(
    cnf::And& term, std::atomic_bool& run) const override;
  private:
  CDCLConfiguration config_;
};

} // tribblesat

#endif // SRC_SAT_CDCL_SAT_H