#ifndef SRC_CLUSTERSAT_NODE_TRIBBLESAT_WRAPPER_H
#define SRC_CLUSTERSAT_NODE_TRIBBLESAT_WRAPPER_H

#include "src/clustersat/protocol/clustersat.grpc.pb.h"
#include "src/tribblesat/sat/sat_strategy.h"

namespace clustersat
{

tribblesat::cnf::And ClustersatAndToTribblesatAnd(clustersat::AndTerm term);

class TribbleSatWrapper {
  public:
  TribbleSatWrapper(tribblesat::SatStrategy& strategy);
  
  clustersat::SatResult GetSatisfiability(clustersat::AndTerm term);

  private:
  tribblesat::SatStrategy& strategy_;
};
} // clustersat

#endif // SRC_CLUSTERSAT_NODE_TRIBBLESAT_WRAPPER_H