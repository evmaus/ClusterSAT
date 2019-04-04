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

#ifndef SRC_SAT_SAT_STRATEGY_H
#define SRC_SAT_SAT_STRATEGY_H

#include "src/simplesat/cnf/cnf_and_op.h"
#include "src/simplesat/cnf/cnf_or_op.h"
#include "src/simplesat/cnf/cnf_variable.h"
#include "src/simplesat/variable_environment/variable_environment.h"
namespace simplesat {
enum SatResultType {
  SAT,
  UNSAT,
  UNKNOWN
};

using SatResult = std::pair<SatResultType, std::vector<int>>;

class SatStrategy {
  public:
  virtual SatResult DetermineCnfSat(cnf::And& term) const = 0;
  virtual SatResult DetermineCnfSatWithCancellation(cnf::And& term, std::atomic_bool& should_run) const = 0;
  virtual ~SatStrategy() {};
};

}
#endif // SRC_SAT_SAT_STRATEGY_H