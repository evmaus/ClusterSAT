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