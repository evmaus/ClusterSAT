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
  TribbleSatServiceImpl(clustersat::TribbleSatWrapper& wrapper) : wrapper_(wrapper) {

  }

  ::grpc::Status CheckSatisfiability(::grpc::ServerContext* context, 
  const ::clustersat::SatRequest* request, 
  ::clustersat::SatResponse* response) override 
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

  void LoadResultFromFuturesMap(int id, ::clustersat::SatResult* result) {
    if (result_map_.at(id).wait_for(std::chrono::seconds(0)) == std::future_status::ready) {
      *(result) = result_map_.at(id).get();
      result->mutable_id()->set_id(id);
    } else {
      result->mutable_id()->set_id(id);
      result->set_result(clustersat::SatResult::IN_PROGRESS);
    }
  }

  ::grpc::Status GetSatisfiabilityResult(::grpc::ServerContext* context, 
  const ::clustersat::SatIdRequest* request, 
  ::clustersat::SatResponse* response) override {
    int id = request->id().id();
    std::lock_guard<std::mutex> guard(result_map_mutex_);
    LoadResultFromFuturesMap(id, response->mutable_result());
  
    return ::grpc::Status::OK;
  }
  ::grpc::Status GetCurrentSatResults(::grpc::ServerContext* context, 
    const ::clustersat::CurrentSatResultsRequest* request, 
    ::clustersat::CurrentSatResultsResponse* response) override {
      
      std::lock_guard<std::mutex> guard(result_map_mutex_);
      for (int i = 0; i < result_map_.size(); i++) {
        SatResult result;
        LoadResultFromFuturesMap(i, &result);
        *(response->add_results()) = result;
      }
      return ::grpc::Status::OK;
  }
  private:
  clustersat::TribbleSatWrapper& wrapper_;
  std::vector<std::shared_future<SatResult>> result_map_;
  std::mutex result_map_mutex_;

};

void RunServer() {
  tribblesat::CDCLConfiguration config(100000000);
  tribblesat::CDCLSatStrategy strategy(config);
  clustersat::TribbleSatWrapper wrapper(strategy);

  std::string server_address("0.0.0.0:50051");
  TribbleSatServiceImpl service(wrapper);

  grpc::ServerBuilder builder;
  // Listen on the given address without any authentication mechanism.
  builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
  // Register "service" as the instance through which we'll communicate with
  // clients. In this case it corresponds to an *synchronous* service.
  builder.RegisterService(&service);
  // Finally assemble the server.
  std::unique_ptr<grpc::Server> server(builder.BuildAndStart());
  std::cout << "Server listening on " << server_address << std::endl;

  // Wait for the server to shutdown. Note that some other thread must be
  // responsible for shutting down the server for this call to ever return.
  server->Wait();
}

} // namespace


int main(int argc, char** argv) {
  clustersat::RunServer();

  return 0;
}
