#ifndef SRC_SAT_BRUTE_FORCE_SAT_H
#define SRC_SAT_BRUTE_FORCE_SAT_H

#include "src/sat/sat_strategy.h"
#include "src/cnf/cnf_and_op.h"
#include "src/cnf/cnf_or_op.h"
#include "src/cnf/cnf_variable.h"
#include "src/cnf/cnf_vector_environment.h"

namespace tribblesat {

// Brute Force SAT Strategy implements a brute force SAT strategy.
class BruteForceSatStrategy : public SatStrategy {
  public:
  BruteForceSatStrategy(uint64_t timeout_ms);  // Handle timeout parameter...
  SatResult DetermineCnfSat(const cnf::And& term) const override;

  private:
  SatResult DetermineCnfSatInternal(
    const cnf::And& term, std::atomic_bool& run) const;
  uint64_t timeout_ms_;
};

} // namespace tribblesat
#endif // SRC_SAT_BRUTE_FORCE_SAT_H