#include <iostream>
#include <memory>
#include <string>
#include <fstream>
#include <sstream>

#include <grpcpp/grpcpp.h>
#include "gflags/gflags.h"

#include "src/clustersat/protocol/clustersat.grpc.pb.h"
#include "src/clustersat/utilities/dimacs_cnf_parser.h"

DEFINE_string(file, "", "DIMACS CNF Format file to run SAT on for submission");
DEFINE_int64(lookup_id, 0, "ID to look up");
DEFINE_string(action, "", "submit, lookup, or list");

namespace clustersat {

class SatClient {
 public:
  SatClient(std::shared_ptr<grpc::Channel> channel)
      : stub_(SATService::NewStub(channel)) {}

  // Assembles the client's payload, sends it and presents the response back
  // from the server.
  SatResult RequestSAT(const clustersat::AndTerm& term) {
    // Data we are sening to the server.
    SatQuery query;
    *query.mutable_term() = term;
    SatRequest request;
    *request.mutable_query() = query;

    // Container for the data we expect from the server.
    SatResponse reply;

    // Context for the client. It could be used to convey extra information to
    // the server and/or tweak certain RPC behaviors.
    grpc::ClientContext context;

    // The actual RPC.
    grpc::Status status = stub_->CheckSatisfiability(&context, request, &reply);

    // Act upon its status.
    if (status.ok()) {
      return reply.result();
    } else {
      std::cout << status.error_code() << ": " << status.error_message()
                << std::endl;
      return SatResult();
    }
  }

  SatResult LookupSAT(const int id) {
    // Data we are sening to the server.
    SatIdRequest request;
    request.mutable_id()->set_id(id);

    // Container for the data we expect from the server.
    SatResponse reply;

    // Context for the client. It could be used to convey extra information to
    // the server and/or tweak certain RPC behaviors.
    grpc::ClientContext context;

    // The actual RPC.
    grpc::Status status = stub_->GetSatisfiabilityResult(&context, request, &reply);

    // Act upon its status.
    if (status.ok()) {
      return reply.result();
    } else {
      std::cout << status.error_code() << ": " << status.error_message()
                << std::endl;
      return SatResult();
    }
  }

  std::vector<SatResult> ListSATResults() {
    // TODO

    return std::vector<SatResult>();
  }
 private:
  std::unique_ptr<SATService::Stub> stub_;
};

std::string PrintableSatResult(SatResult result) {
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

} // namespace clustersat;

int main(int argc, char** argv) {
  gflags::ParseCommandLineFlags(&argc, &argv, true);
  
  // Instantiate the client. It requires a channel, out of which the actual RPCs
  // are created. This channel models a connection to an endpoint (in this case,
  // localhost at port 50051). We indicate that the channel isn't authenticated
  // (use of InsecureChannelCredentials()).

  clustersat::SatClient client(grpc::CreateChannel(
      "localhost:50051", grpc::InsecureChannelCredentials()));
  
  if (FLAGS_action == "submit") {
    std::ifstream file(FLAGS_file);
    clustersat::DiMacsParser parser;
    clustersat::SatResult reply = client.RequestSAT(parser.ParseCnf(file));
    std::cout << "Client received: " << clustersat::PrintableSatResult(reply) << std::endl;
  } else if (FLAGS_action == "lookup") {
    clustersat::SatResult reply = client.LookupSAT(FLAGS_lookup_id);
    std::cout << "Client received: " << clustersat::PrintableSatResult(reply) << std::endl;
  } else if (FLAGS_action == "list") {
    std::vector<clustersat::SatResult> results = client.ListSATResults();
    std::cout << "Client received: " << std::endl;
    for(auto result : results) {
      std::cout << clustersat::PrintableSatResult(result) << std::endl;
    }
  } else {
    std::cout << "Unknown action; not submit/lookup/list. Recieved: " << FLAGS_action << std::endl;
  }
  
  return 0;
}