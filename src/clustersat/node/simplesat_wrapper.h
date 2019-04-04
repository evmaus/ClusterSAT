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

#ifndef SRC_CLUSTERSAT_NODE_TRIBBLESAT_WRAPPER_H
#define SRC_CLUSTERSAT_NODE_TRIBBLESAT_WRAPPER_H

#include "src/clustersat/protocol/clustersat.grpc.pb.h"
#include "src/simplesat/sat/sat_strategy.h"

namespace clustersat
{

simplesat::cnf::And ClustersatAndToTribblesatAnd(clustersat::AndTerm term);

class SimpleSatWrapper {
  public:
  SimpleSatWrapper(simplesat::SatStrategy& strategy);
  
  clustersat::SatResult GetSatisfiability(clustersat::AndTerm term, std::atomic_bool& should_run);

  private:
  simplesat::SatStrategy& strategy_;
};
} // clustersat

#endif // SRC_CLUSTERSAT_NODE_TRIBBLESAT_WRAPPER_H