/*
 * Copyright 2019 Google LLC
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

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