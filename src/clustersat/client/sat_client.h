#ifndef SRC_CLUSTERSAT_CLIENT_SAT_CLIENT_IMPL_H
#define SRC_CLUSTERSAT_CLIENT_SAT_CLIENT_IMPL_H

#include <iostream>
#include <memory>
#include <string>
#include <fstream>
#include <sstream>

#include <grpcpp/grpcpp.h>
#include "gflags/gflags.h"

#include "src/clustersat/protocol/clustersat.grpc.pb.h"

namespace clustersat {

class SatClient {
  public:
  virtual ~SatClient() {}
  virtual SatResult RequestSAT(const clustersat::AndTerm& term, SatRequestIdentifier id) = 0;
  virtual SatResult LookupSAT(const int id) = 0;
  virtual std::vector<SatResult> ListSATResults() = 0;
};

class SatClientImpl : public SatClient {
 public:
  SatClientImpl(std::shared_ptr<grpc::Channel> channel);

  // Assembles the client's payload, sends it and presents the response back
  // from the server.
  SatResult RequestSAT(const clustersat::AndTerm& term, SatRequestIdentifier id) override;

  SatResult LookupSAT(const int id) override;

  std::vector<SatResult> ListSATResults() override;

 private:
  std::unique_ptr<SATService::Stub> stub_;
};


} // namespace clustersat;
#endif // SRC_CLUSTERSAT_CLIENT_SAT_CLIENT_IMPL_H