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