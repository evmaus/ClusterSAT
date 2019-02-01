#include "src/clustersat/leader/leader.h"

#include <glog/logging.h>

namespace clustersat {

// SolverNode:
::util::StatusOr<SatResult> SolverNode::SubmitResult(SatRequestIdentifier id, SatQuery query) 
{
  return client_.RequestSAT(query.term(), id);
}

::util::StatusOr<SatResult> SolverNode::GetNodeResult(SatRequestIdentifier id)
{
  return client_.LookupSAT(id.id());
}

// End SolverNode


// LeaderNode:
LeaderNode::LeaderNode(std::vector<SolverNode> nodes) : nodes_(nodes) 
{
}

SatRequestIdentifier LeaderNode::StartSatisfiability(SatQuery query)
{
  SatRequestIdentifier identifier;
  // Register the query by ID
  {
    std::lock_guard<std::mutex> guard(solver_queries_mutex_);
    solver_queries_.push_back(query);
    identifier.set_id(solver_queries_.size()-1);
    LOG(INFO) << "Assigned id " << identifier.id() << " to the request";
  }

  // Submit to each node.
  for (auto node : nodes_) {
    node.SubmitResult(identifier, query);
  }

  return identifier;
}

SatResult LeaderNode::GetSatResultFromNodes(SatRequestIdentifier id)
{
  for (auto node : nodes_)
  {
    SatResult intermediate = node.GetNodeResult(id).ValueOrDie();
    if (intermediate.result() != clustersat::SatResult::IN_PROGRESS) {
      return intermediate;
    }
  }
  SatResult result;
  *result.mutable_id() = id;
  result.set_result(clustersat::SatResult::IN_PROGRESS);
  return result;
}


// Get SAT Results for a particular request
SatResult LeaderNode::GetSatisfiabilityResult(SatRequestIdentifier id) {
  return GetSatResultFromNodes(id);
}

// Returns the current status of all satisfiability requests
std::vector<SatResult> LeaderNode::GetCurrentSatRequestStatuses(std::vector<SatRequestIdentifier> ids) {
  std::vector<SatResult> results;
  for (int i = 0; i < solver_queries_.size(); i++) {
      SatRequestIdentifier id;
      id.set_id(i);
      results.push_back(GetSatResultFromNodes(id));
  }
  return results;
}

// End LeaderNode

// LeaderSatServiceImpl

LeaderSATServiceImpl::LeaderSATServiceImpl (LeaderNode& node) 
  : node_(node)
{

}

::grpc::Status LeaderSATServiceImpl::CheckSatisfiability(::grpc::ServerContext* context,  
    const ::clustersat::SatRequest* request, 
    ::clustersat::SatResponse* response)
{
  LOG(INFO) << "Recieved SAT request." << std::endl;
  *response->mutable_result()->mutable_id() = node_.StartSatisfiability(request->query());
  response->mutable_result()->set_result(clustersat::SatResult::IN_PROGRESS);
  LOG(INFO) << "Processed SAT request." << std::endl;
  return ::grpc::Status::OK;
}
::grpc::Status LeaderSATServiceImpl::GetSatisfiabilityResult(::grpc::ServerContext* context, 
    const ::clustersat::SatIdRequest* request, 
    ::clustersat::SatResponse* response)
{

  LOG(INFO) << "Recieved request for id " << request->id().id() << std::endl;
  *response->mutable_result() = node_.GetSatisfiabilityResult(request->id());
  return ::grpc::Status::OK;
}
::grpc::Status LeaderSATServiceImpl::GetCurrentSatResults(::grpc::ServerContext* context, 
  const ::clustersat::CurrentSatResultsRequest* request, 
  ::clustersat::CurrentSatResultsResponse* response) 
{
  std::vector<SatRequestIdentifier> ids;
  for (auto id_request : request->request())
  {
      ids.push_back(id_request);
  }

  std::vector<SatResult> results = node_.GetCurrentSatRequestStatuses(ids);
  
  for (auto result : results) {
    *(response->add_results()) = result;
  }

  return ::grpc::Status::OK;
}

// End LeaderSatServiceImpl

} // namespace clustersat