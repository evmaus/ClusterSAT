#include <string>
#include <grpcpp/grpcpp.h>
#include <glog/logging.h>

#include "src/clustersat/protocol/clustersat.grpc.pb.h"
#include "src/clustersat/leader/leader.h"
#include "absl/strings/str_split.h"

DEFINE_string(listening_address, "0.0.0.0:50051", "IP and Port to listen on");
DEFINE_string(node_addresses, "localhost:50052", "Nodes to distribute to, semicolon separated");

void RunServer(std::string server_address, std::string node_addresses) {
  std::vector<std::string> node_addrs = absl::StrSplit(node_addresses, ';', absl::SkipEmpty());

  std::vector<clustersat::SolverNode> nodes;
  for (auto addr : node_addrs) {
    clustersat::SatClientImpl* client = new clustersat::SatClientImpl(grpc::CreateChannel(
        addr, grpc::InsecureChannelCredentials()));
    nodes.push_back(clustersat::SolverNode(*client));
    LOG(INFO) << "Added node for server " << addr << std::endl;
  }
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
  LOG(INFO) << "Server listening on " << server_address << std::endl;

  // Wait for the server to shutdown. Note that some other thread must be
  // responsible for shutting down the server for this call to ever return.
  server->Wait();
}

int main(int argc, char** argv) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, true);

  RunServer(FLAGS_listening_address, FLAGS_node_addresses);
  return 0;
}