#ifndef SRC_SAT_CDCL_SAT_H
#define SRC_SAT_CDCL_SAT_H

#include "src/simplesat/sat/sat_strategy.h"
#include "src/simplesat/cnf/cnf_and_op.h"
#include "src/simplesat/cnf/cnf_or_op.h"
#include "src/simplesat/cnf/cnf_variable.h"
#include "src/simplesat/sat/cdcl_configuration.h"

namespace simplesat {

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

} // simplesat

#endif // SRC_SAT_CDCL_SAT_H