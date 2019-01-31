#include <string>
#include <grpcpp/grpcpp.h>

#include "src/clustersat/protocol/clustersat.grpc.pb.h"
#include "src/clustersat/leader/leader.h"

void RunServer() {
  std::string server_address("0.0.0.0:50051");

  clustersat::SatClientImpl client(grpc::CreateChannel(
      "localhost:50052", grpc::InsecureChannelCredentials()));
  std::vector<clustersat::SolverNode> nodes;
  nodes.push_back(clustersat::SolverNode(client));
  clustersat::LeaderNode leader(nodes);
  clustersat::LeaderSATServiceImpl service(leader);

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
  RunServer();
  return 0;
}