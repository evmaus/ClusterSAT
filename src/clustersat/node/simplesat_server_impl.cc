// Copyright 2019 Google LLC
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.


#include "src/clustersat/node/simplesat_server_impl.h"

#include <glog/logging.h>

namespace clustersat {
SimpleSatServiceImpl::SimpleSatServiceImpl(clustersat::SimpleSatWrapper& wrapper) : wrapper_(wrapper) {

}

::grpc::Status SimpleSatServiceImpl::CheckSatisfiability(::grpc::ServerContext* context, 
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

void SimpleSatServiceImpl::LoadResultFromFuturesMap(int id, ::clustersat::SatResult* result) {
  if (result_map_.at(id).result.wait_for(std::chrono::seconds(0)) == std::future_status::ready) {
    *(result) = result_map_.at(id).result.get();
    result->mutable_id()->set_id(id);
  } else {
    result->mutable_id()->set_id(id);
    result->set_result(clustersat::SatResult::IN_PROGRESS);
  }
}

::grpc::Status SimpleSatServiceImpl::GetSatisfiabilityResult(::grpc::ServerContext* context, 
const ::clustersat::SatIdRequest* request, 
::clustersat::SatResponse* response) {
  int id = request->id().id();
  std::lock_guard<std::mutex> guard(result_map_mutex_);
  LoadResultFromFuturesMap(id, response->mutable_result());

  return ::grpc::Status::OK;
}
::grpc::Status SimpleSatServiceImpl::GetCurrentSatResults(::grpc::ServerContext* context, 
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

::grpc::Status SimpleSatServiceImpl::CancelSatRequest(::grpc::ServerContext* context, 
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