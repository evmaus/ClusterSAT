
#include "src/clustersat/node/tribblesat_server_impl.h"

namespace clustersat {
TribbleSatServiceImpl::TribbleSatServiceImpl(clustersat::TribbleSatWrapper& wrapper) : wrapper_(wrapper) {

}

::grpc::Status TribbleSatServiceImpl::CheckSatisfiability(::grpc::ServerContext* context, 
const ::clustersat::SatRequest* request, 
::clustersat::SatResponse* response) 
{
  auto term = request->query().term();
  std::shared_future<SatResult> future = std::async(std::launch::async, 
    [this, term]() 
    {
      return this->wrapper_.GetSatisfiability(term);
    }
  );
  {
    std::lock_guard<std::mutex> guard(result_map_mutex_);
    result_map_.push_back(future);
    int id = result_map_.size()-1;

    response->mutable_result()->mutable_id()->set_id(id);
    response->mutable_result()->set_result(clustersat::SatResult::IN_PROGRESS);

  }
  return ::grpc::Status::OK;
}

void TribbleSatServiceImpl::LoadResultFromFuturesMap(int id, ::clustersat::SatResult* result) {
  if (result_map_.at(id).wait_for(std::chrono::seconds(0)) == std::future_status::ready) {
    *(result) = result_map_.at(id).get();
    result->mutable_id()->set_id(id);
  } else {
    result->mutable_id()->set_id(id);
    result->set_result(clustersat::SatResult::IN_PROGRESS);
  }
}

::grpc::Status TribbleSatServiceImpl::GetSatisfiabilityResult(::grpc::ServerContext* context, 
const ::clustersat::SatIdRequest* request, 
::clustersat::SatResponse* response) {
  int id = request->id().id();
  std::lock_guard<std::mutex> guard(result_map_mutex_);
  LoadResultFromFuturesMap(id, response->mutable_result());

  return ::grpc::Status::OK;
}
::grpc::Status TribbleSatServiceImpl::GetCurrentSatResults(::grpc::ServerContext* context, 
  const ::clustersat::CurrentSatResultsRequest* request, 
  ::clustersat::CurrentSatResultsResponse* response) {
    
    std::lock_guard<std::mutex> guard(result_map_mutex_);
    for (int i = 0; i < result_map_.size(); i++) {
      SatResult result;
      LoadResultFromFuturesMap(i, &result);
      *(response->add_results()) = result;
    }
    return ::grpc::Status::OK;
}
} // namespace clustersat