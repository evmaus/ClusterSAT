
#include "src/clustersat/node/tribblesat_server_impl.h"

namespace clustersat {
TribbleSatServiceImpl::TribbleSatServiceImpl(clustersat::TribbleSatWrapper& wrapper) : wrapper_(wrapper) {

}

::grpc::Status TribbleSatServiceImpl::CheckSatisfiability(::grpc::ServerContext* context, 
const ::clustersat::SatRequest* request, 
::clustersat::SatResponse* response) 
{
  auto term = request->query().term();
  int id = request->id().id();
  
  {
    std::lock_guard<std::mutex> guard(result_map_mutex_);
    result_map_[id].should_run = true;

    std::shared_future<SatResult> future = std::async(std::launch::async, 
      [this, term, id]() 
      {
        return this->wrapper_.GetSatisfiability(term, this->result_map_[id].should_run);
      }
    );
    result_map_[id].result = future;  

    response->mutable_result()->mutable_id()->set_id(id);
    response->mutable_result()->set_result(clustersat::SatResult::IN_PROGRESS);
  }
  return ::grpc::Status::OK;
}

void TribbleSatServiceImpl::LoadResultFromFuturesMap(int id, ::clustersat::SatResult* result) {
  if (result_map_.at(id).result.wait_for(std::chrono::seconds(0)) == std::future_status::ready) {
    *(result) = result_map_.at(id).result.get();
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

::grpc::Status TribbleSatServiceImpl::CancelSatRequest(::grpc::ServerContext* context, 
    const ::clustersat::SatIdRequest* request, 
    ::clustersat::SatResponse* response) 
{
  result_map_.at(request->id().id()).should_run = false;

  result_map_.at(request->id().id()).result.wait();

  SatResult result = result_map_.at(request->id().id()).result.get();
  result.set_result(SatResult::CANCELLED);

  *response->mutable_result() = result;
  return ::grpc::Status::OK;
}

} // namespace clustersat