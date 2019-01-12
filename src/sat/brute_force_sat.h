#ifndef SRC_SAT_BRUTE_FORCE_SAT_H
#define SRC_SAT_BRUTE_FORCE_SAT_H

#include "src/sat/sat_strategy.h"
#include "src/model/function.h"

namespace tribblesat {

class BruteForceSatStrategy : public SatStrategy {
  public:
  BruteForceSatStrategy(uint64_t timeout_ms);  // Handle timeout parameter...
  SatResultType DetermineSat(const Function& function) const override;

  private:
  SatResultType DetermineSatInternal(
    const Function& function, std::atomic_bool& run) const;
  uint64_t timeout_ms_;
};

} // namespace tribblesat
#endif // SRC_SAT_BRUTE_FORCE_SAT_H