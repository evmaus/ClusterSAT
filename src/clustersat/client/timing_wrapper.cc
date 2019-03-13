#include <iostream>
#include <memory>
#include <string>
#include <fstream>
#include <sstream>
#include <thread>
#include <chrono>

#include <grpcpp/grpcpp.h>
#include <glog/logging.h>
#include "gflags/gflags.h"


#include "src/clustersat/protocol/clustersat.grpc.pb.h"
#include "src/clustersat/utilities/dimacs_cnf_parser.h"
#include "src/clustersat/client/sat_client.h"

DEFINE_string(file, "", "DIMACS CNF Format file to run SAT on for submission");
DEFINE_string(server, "localhost:50051", "Server to use");

std::string PrintableSatResult(clustersat::SatResult result) {
  std::ostringstream stream;
  stream << "Id: " << result.id().id() << std::endl;
  stream << "Status: " << result.result() << std::endl;
  stream << "[ ";
  for (auto term : result.assignments()) {
    stream << term.id() << " ";
  }
  stream << " ]";
  return stream.str();
}

int main(int argc, char** argv) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, true);
  
  // Instantiate the client. It requires a channel, out of which the actual RPCs
  // are created. This channel models a connection to an endpoint (in this case,
  // localhost at port 50051). We indicate that the channel isn't authenticated
  // (use of InsecureChannelCredentials()).

  clustersat::SatClientImpl client(grpc::CreateChannel(
      FLAGS_server, grpc::InsecureChannelCredentials()));
  
  std::ifstream file(FLAGS_file);
  clustersat::DiMacsParser parser;
  
  auto start = std::chrono::high_resolution_clock::now();

  auto result = client.RequestSAT(parser.ParseCnf(file), clustersat::SatRequestIdentifier());
  int id = 0;
  if (result.ok()) {
    clustersat::SatResult reply = result.ValueOrDie();
    id = result.ValueOrDie().id().id();
  } else {
    std::cout << "Encountered an error" << std::endl;
  }
  
  auto lookup = client.LookupSAT(id);
  while (lookup.ok() && (lookup.ValueOrDie().result() == clustersat::SatResult::IN_PROGRESS
    || lookup.ValueOrDie().result() == clustersat::SatResult::NOT_STARTED))
  {
    std::this_thread::sleep_for (std::chrono::milliseconds(100));
    lookup = client.LookupSAT(id);
  }

  auto end = std::chrono::high_resolution_clock::now();

  std::cout << "Client complete: " << PrintableSatResult(lookup.ValueOrDie()) << std::endl;
  std::cout << "Time taken: " << std::chrono::duration_cast<
        std::chrono::duration<double>>(end - start).count() << std::endl;
  return 0;
}