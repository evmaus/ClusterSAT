#include <string>
#include <grpcpp/grpcpp.h>

#include "src/clustersat/protocol/clustersat.grpc.pb.h"

class LeaderSATServiceImpl final : public clustersat::SATService::Service {
  ::grpc::Status CheckSatisfiability(::grpc::ServerContext* context, 
  const ::clustersat::SatRequest* request, 
  ::clustersat::SatResponse* response) override {
      // TODO
      return ::grpc::Status::OK;
  }
  ::grpc::Status GetSatisfiabilityResult(::grpc::ServerContext* context, 
  const ::clustersat::SatIdRequest* request, 
  ::clustersat::SatResponse* response) override {
      // TODO
      return ::grpc::Status::OK;
  }
  ::grpc::Status GetCurrentSatResults(::grpc::ServerContext* context, 
    const ::clustersat::CurrentSatResultsRequest* request, 
    ::clustersat::CurrentSatResultsResponse* response) override {
      // TODO
      return ::grpc::Status::OK;
  }
  
};

void RunServer() {
  std::string server_address("0.0.0.0:50051");

  LeaderSATServiceImpl service;

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

int main() {
  return 0;
}