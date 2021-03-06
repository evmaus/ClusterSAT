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

#include <iostream>
#include <memory>
#include <string>
#include <fstream>
#include <sstream>


#include <grpcpp/grpcpp.h>
#include <glog/logging.h>
#include "gflags/gflags.h"


#include "src/clustersat/protocol/clustersat.grpc.pb.h"
#include "src/clustersat/utilities/dimacs_cnf_parser.h"
#include "src/clustersat/client/sat_client.h"

DEFINE_string(file, "", "DIMACS CNF Format file to run SAT on for submission");
DEFINE_int64(lookup_id, 0, "ID to look up");
DEFINE_string(action, "", "submit, lookup, or list");
DEFINE_string(server, "localhost:50051", "Server to look up");

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
  
  if (FLAGS_action == "submit") {
    std::ifstream file(FLAGS_file);
    clustersat::DiMacsParser parser;
    auto result = client.RequestSAT(parser.ParseCnf(file), clustersat::SatRequestIdentifier());
    if (result.ok()) {
      clustersat::SatResult reply = result.ValueOrDie();
      std::cout << "Client received: " << PrintableSatResult(reply) << std::endl;
    } else {
      std::cout << "Encountered an error" << std::endl;
    }
  } else if (FLAGS_action == "lookup") {
    auto result = client.LookupSAT(FLAGS_lookup_id);
    if (result.ok()) {
      clustersat::SatResult reply = result.ValueOrDie();
      std::cout << "Client received: " << PrintableSatResult(reply) << std::endl;
    } else {
      std::cout << "Encountered an error" << std::endl;
    }
  } else if (FLAGS_action == "list") {
    auto result = client.ListSATResults();
    if (result.ok()) {
      std::vector<clustersat::SatResult> results = result.ValueOrDie();
      std::cout << "Client received: " << std::endl;
      for(auto result : results) {
        std::cout << PrintableSatResult(result) << std::endl;
      }
    } else {
      std::cout << "Encountered an error" << std::endl;
    }
  } else if (FLAGS_action == "cancel") {
    auto result = client.CancelSAT(FLAGS_lookup_id);
    if (result.ok()) {
      clustersat::SatResult reply = result.ValueOrDie();
      std::cout << "Client received: " << PrintableSatResult(reply) << std::endl;
    } else {
      std::cout << "Encountered an error" << std::endl;
    }
  } else {
    std::cout << "Unknown action; not submit/lookup/list. Recieved: " << FLAGS_action << std::endl;
  }
  
  return 0;
}