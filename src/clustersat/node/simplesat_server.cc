#include <string>
#include <vector>
#include <future>
#include <grpcpp/grpcpp.h>
#include <glog/logging.h>

#include "src/clustersat/protocol/clustersat.grpc.pb.h"
#include "src/clustersat/node/simplesat_wrapper.h"
#include "src/simplesat/sat/cdcl_sat.h"
#include "src/simplesat/sat/cdcl_configuration.h"
#include "src/clustersat/node/simplesat_server_impl.h"

#include "gflags/gflags.h"


DEFINE_string(listening_address, "0.0.0.0:50051", "IP and Port to listen on");
DEFINE_string(configuration, "default", "configuration to use: default or linear");

void RunServer(std::string server_address) {
  
  // Default config.
  simplesat::CDCLConfiguration config(30000000, 
    simplesat::VariableSelectorType::VSIDS, 
    simplesat::CompactingPolicyType::TERM_SIZE,
    simplesat::RestartPolicyType::GEOMETRIC);
  
  // Use linear if the flag says to.
  if (FLAGS_configuration == "linear") {
    config = simplesat::CDCLConfiguration(3000000,
    simplesat::VariableSelectorType::LINEAR,
    simplesat::CompactingPolicyType::TERM_SIZE,
    simplesat::RestartPolicyType::GEOMETRIC);
  }

  simplesat::CDCLSatStrategy strategy(config);
  clustersat::SimpleSatWrapper wrapper(strategy);

  clustersat::SimpleSatServiceImpl service(wrapper);

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
