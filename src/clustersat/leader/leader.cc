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

::util::StatusOr<SatResult> SolverNode::CancelRequest(SatRequestIdentifier id) {
  return client_.CancelSAT(id.id());
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
    result.result.set_result(SatResult::NOT_STARTED);
    *result.result.mutable_id() = identifier;
    solver_queries_.push_back(result);
    LOG(INFO) << "Assigned id " << identifier.id() << " to the request";
  }

  return identifier;
}

void LeaderNode::StepServer() {
  int size = solver_queries_.size();
  for (int i = 0; i < size; i++) {
    // We can lock inside the loop because we never remove things from the solver_queries_.
    std::lock_guard<std::mutex> guard(solver_queries_mutex_);
    SatQueryAndResult& current = solver_queries_[i];
    if (current.result.result() == SatResult::NOT_STARTED) {
      LOG(INFO) << "Starting SAT on id " << current.id << std::endl;
      // Submit to each node.
      for (int i = 0; i < nodes_.size(); i++) {
        nodes_.at(i).SubmitResult(current.result.id(), current.query);
        current.solving_nodes.push_back(i);
      }
      current.result.set_result(SatResult::IN_PROGRESS);
    } else if (current.result.result() == SatResult::IN_PROGRESS) {
      bool all_unknown = true;
      for (auto node : nodes_)
      {
        auto result = node.GetNodeResult(current.result.id());
        if(result.ok()) {
          SatResult intermediate = result.ValueOrDie();
          if (intermediate.result() == clustersat::SatResult::SAT 
              || intermediate.result() == clustersat::SatResult::UNSAT) {
            LOG(INFO) << "Got result " << intermediate.result() << " from node." << std::endl;
            current.result = intermediate;
            all_unknown = false;
            break;
          }
          if (intermediate.result() != SatResult::UNKNOWN) {
            all_unknown = false;
          }
        } else {
          LOG(ERROR) << "Error retrieving result id" << current.id << " from node " << std::endl;
        }
      }
      if (all_unknown) {
        LOG(INFO) << "Got unknown results from all nodes on id " << current.id << std::endl;
        current.result.set_result(SatResult::UNKNOWN);
      }
    } else if (current.result.result() == SatResult::CANCELLING) {
      for (auto node : nodes_) {
        node.CancelRequest(current.result.id());
      }
      current.result.set_result(SatResult::CANCELLED);
    }
  }
}

SatResult LeaderNode::GetSatResultFromNodes(SatRequestIdentifier id)
{
  // TODO: Bounds check here.
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

SatResult LeaderNode::CancelSatisfiability(SatRequestIdentifier id) {
  LOG(INFO) << "Cancelling task " << id.id();
  std::lock_guard<std::mutex> guard(solver_queries_mutex_);
  if (solver_queries_.at(id.id()).result.result() == SatResult::IN_PROGRESS) {
    solver_queries_.at(id.id()).result.set_result(SatResult::CANCELLING);
  }
  return solver_queries_.at(id.id()).result;
}

// End LeaderNode

// LeaderSatServiceImpl

LeaderSATServiceImpl::LeaderSATServiceImpl (LeaderNode& node) 
  : node_(node),
  main_loop_thread_([this](){ this->MainEventThread(); })
{
  
}

void LeaderSATServiceImpl::MainEventThread() {
  while(true) {
    node_.StepServer();
    std::this_thread::sleep_for(std::chrono::seconds(1));
  }
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

::grpc::Status LeaderSATServiceImpl::CancelSatRequest(::grpc::ServerContext* context, 
    const ::clustersat::SatIdRequest* request, 
    ::clustersat::SatResponse* response) 
{
  LOG(INFO) << "Recieved cancellation for " << request->id().id() << std::endl;

  *response->mutable_result() = node_.CancelSatisfiability(request->id());
  return ::grpc::Status::OK;
}


// End LeaderSatServiceImpl

} // namespace clustersat