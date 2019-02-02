#ifndef SRC_CLUSTERSAT_NODE_TRIBBLESAT_SERVER_IMPL_H
#define SRC_CLUSTERSAT_NODE_TRIBBLESAT_SERVER_IMPL_H
#include <string>
#include <vector>
#include <future>
#include <grpcpp/grpcpp.h>

#include "src/clustersat/protocol/clustersat.grpc.pb.h"
#include "src/clustersat/node/tribblesat_wrapper.h"
#include "src/tribblesat/sat/cdcl_sat.h"
#include "src/tribblesat/sat/cdcl_configuration.h"

namespace clustersat {

class TribbleSatServiceImpl final : public clustersat::SATService::Service {
  public:
  TribbleSatServiceImpl(clustersat::TribbleSatWrapper& wrapper);

  ::grpc::Status CheckSatisfiability(::grpc::ServerContext* context, 
  const ::clustersat::SatRequest* request, 
  ::clustersat::SatResponse* response) override;

  void LoadResultFromFuturesMap(int id, ::clustersat::SatResult* result);

  ::grpc::Status GetSatisfiabilityResult(::grpc::ServerContext* context, 
  const ::clustersat::SatIdRequest* request, 
  ::clustersat::SatResponse* response) override;

  ::grpc::Status GetCurrentSatResults(::grpc::ServerContext* context, 
    const ::clustersat::CurrentSatResultsRequest* request, 
    ::clustersat::CurrentSatResultsResponse* response) override;
  
  ::grpc::Status CancelSatRequest(::grpc::ServerContext* context, 
    const ::clustersat::SatIdRequest* request, 
    ::clustersat::SatResponse* response) override;

  private:
  clustersat::TribbleSatWrapper& wrapper_;
  std::vector<std::shared_future<SatResult>> result_map_;
  std::mutex result_map_mutex_;
};

} // namespace clustersat

#endif // SRC_CLUSTERSAT_NODE_TRIBBLESAT_SERVER_IMPL_H