#include <string>
#include <vector>
#include <future>
#include <grpcpp/grpcpp.h>
#include <glog/logging.h>

#include "src/clustersat/protocol/clustersat.grpc.pb.h"
#include "src/clustersat/node/tribblesat_wrapper.h"
#include "src/tribblesat/sat/cdcl_sat.h"
#include "src/tribblesat/sat/cdcl_configuration.h"
#include "src/clustersat/node/tribblesat_server_impl.h"

#include "gflags/gflags.h"


DEFINE_string(listening_address, "0.0.0.0:50051", "IP and Port to listen on");

void RunServer(std::string server_address) {
  tribblesat::CDCLConfiguration config(100000000);
  tribblesat::CDCLSatStrategy strategy(config);
  clustersat::TribbleSatWrapper wrapper(strategy);

  clustersat::TribbleSatServiceImpl service(wrapper);

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

int main(int argc, char** argv) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, true);

  RunServer(FLAGS_listening_address);

  return 0;
}
