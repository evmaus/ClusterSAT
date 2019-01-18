#ifndef SRC_SAT_CDCL_SAT_H
#define SRC_SAT_CDCL_SAT_H

#include "src/sat/sat_strategy.h"
#include "src/cnf/cnf_and_op.h"
#include "src/cnf/cnf_or_op.h"
#include "src/cnf/cnf_variable.h"

namespace tribblesat {

class CDCLSatStrategy : public SatStrategy {
  public:
  CDCLSatStrategy(uint64_t timeout_ms);  // Handle timeout parameter...
  SatResult DetermineCnfSat(const cnf::And& term) const override;

  private:
  SatResult DetermineCnfSatInternal(
    const cnf::And& term, std::atomic_bool& run) const;
  uint64_t timeout_ms_;
};

} // tribblesat

#endif // SRC_SAT_CDCL_SAT_H