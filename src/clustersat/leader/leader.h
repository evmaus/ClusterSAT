#ifndef SRC_CLUSTERSAT_LEADER_LEADER_H
#define SRC_CLUSTERSAT_LEADER_LEADER_H

#include <string>
#include <thread>
#include <grpcpp/grpcpp.h>

#include "src/clustersat/protocol/clustersat.grpc.pb.h"
#include "src/clustersat/client/sat_client.h"

namespace clustersat {

class SolverNode {
  public:
  SolverNode(SatClient& client) : client_(client) {}

  ::util::StatusOr<SatResult> SubmitResult(SatRequestIdentifier id, SatQuery query);

  ::util::StatusOr<SatResult> GetNodeResult(SatRequestIdentifier id);

  ::util::StatusOr<SatResult> CancelRequest(SatRequestIdentifier id);

  private:
  SatClient& client_;
};

struct SatQueryAndResult {
  int id;
  SatQuery query;
  SatResult result;
  std::vector<int> solving_nodes;
};

class LeaderNode {
  public:
  // Create a leader node with the attached solver nodes.
  LeaderNode(std::vector<SolverNode> nodes);

  // Start computing satisfiability on all compute nodes
  SatRequestIdentifier StartSatisfiability(SatQuery query);
  
  // Get SAT Results for a particular request
  SatResult GetSatisfiabilityResult(SatRequestIdentifier id);

  // Returns the current status of all satisfiability requests
  std::vector<SatResult> GetCurrentSatRequestStatuses(std::vector<SatRequestIdentifier> ids);

  SatResult CancelSatisfiability(SatRequestIdentifier id);

  void StepServer();

  private:
  SatResult GetSatResultFromNodes(SatRequestIdentifier id);

  std::mutex solver_queries_mutex_;
  std::vector<SatQueryAndResult> solver_queries_;

  std::mutex nodes_mutex_;
  std::vector<SolverNode> nodes_;


};

class LeaderSATServiceImpl final : public clustersat::SATService::Service {
  public:
  LeaderSATServiceImpl(LeaderNode& node);

  void MainEventThread();

  ::grpc::Status CheckSatisfiability(::grpc::ServerContext* context, 
    const ::clustersat::SatRequest* request, 
    ::clustersat::SatResponse* response) override;

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
  LeaderNode& node_;
  std::thread main_loop_thread_;
};



} // namespace clustersat
#endif // SRC_CLUSTERSAT_LEADER_LEADER_H