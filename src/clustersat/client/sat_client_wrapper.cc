#include <iostream>
#include <memory>
#include <string>
#include <fstream>
#include <sstream>

#include <grpcpp/grpcpp.h>
#include "gflags/gflags.h"

#include "src/clustersat/protocol/clustersat.grpc.pb.h"
#include "src/clustersat/utilities/dimacs_cnf_parser.h"
#include "src/clustersat/client/sat_client.h"

DEFINE_string(file, "", "DIMACS CNF Format file to run SAT on for submission");
DEFINE_int64(lookup_id, 0, "ID to look up");
DEFINE_string(action, "", "submit, lookup, or list");

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
  gflags::ParseCommandLineFlags(&argc, &argv, true);
  
  // Instantiate the client. It requires a channel, out of which the actual RPCs
  // are created. This channel models a connection to an endpoint (in this case,
  // localhost at port 50051). We indicate that the channel isn't authenticated
  // (use of InsecureChannelCredentials()).

  clustersat::SatClientImpl client(grpc::CreateChannel(
      "localhost:50051", grpc::InsecureChannelCredentials()));
  
  if (FLAGS_action == "submit") {
    std::ifstream file(FLAGS_file);
    clustersat::DiMacsParser parser;
    clustersat::SatResult reply = client.RequestSAT(parser.ParseCnf(file), clustersat::SatRequestIdentifier());
    std::cout << "Client received: " << PrintableSatResult(reply) << std::endl;
  } else if (FLAGS_action == "lookup") {
    clustersat::SatResult reply = client.LookupSAT(FLAGS_lookup_id);
    std::cout << "Client received: " << PrintableSatResult(reply) << std::endl;
  } else if (FLAGS_action == "list") {
    std::vector<clustersat::SatResult> results = client.ListSATResults();
    std::cout << "Client received: " << std::endl;
    for(auto result : results) {
      std::cout << PrintableSatResult(result) << std::endl;
    }
  } else {
    std::cout << "Unknown action; not submit/lookup/list. Recieved: " << FLAGS_action << std::endl;
  }
  
  return 0;
}