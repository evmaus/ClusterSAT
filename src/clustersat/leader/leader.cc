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
  SatQueryAndResult result;
  // Register the query by ID
  {
    std::lock_guard<std::mutex> guard(solver_queries_mutex_);
    identifier.set_id(solver_queries_.size());

    result.id = identifier.id();
    result.query = query;
    result.result.set_result(SatResult::IN_PROGRESS);
    *result.result.mutable_id() = identifier;
    solver_queries_.push_back(result);
    LOG(INFO) << "Assigned id " << identifier.id() << " to the request";

    // Submit to each node.
    for (int i = 0; i < nodes_.size(); i++) {
      nodes_.at(i).SubmitResult(identifier, query);
      solver_queries_.at(identifier.id()).solving_nodes.push_back(i);
    }
  }

  return identifier;
}

SatResult LeaderNode::GetSatResultFromNodes(SatRequestIdentifier id)
{
  // TODO: Bounds check here.
  if (solver_queries_.at(id.id()).result.result() == SatResult::IN_PROGRESS) {
    bool all_unknown = true;
    for (auto node : nodes_)
    {
      auto result = node.GetNodeResult(id);
      if(result.ok()) {
        SatResult intermediate = result.ValueOrDie();
        if (intermediate.result() == clustersat::SatResult::SAT 
            || intermediate.result() == clustersat::SatResult::UNSAT) {
          solver_queries_.at(id.id()).result = intermediate;
          all_unknown = false;
          break;
        }
        if (intermediate.result() != SatResult::UNKNOWN) {
          all_unknown = false;
        }
      } else {
        LOG(ERROR) << "Error retrieving result id" << id.id() << " from node " << std::endl;
      }
    }
    if (all_unknown) {
      solver_queries_.at(id.id()).result.set_result(SatResult::UNKNOWN);
    }
  }
  
  return solver_queries_.at(id.id()).result;
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