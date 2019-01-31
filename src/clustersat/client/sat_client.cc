
#include "src/clustersat/client/sat_client.h"

namespace clustersat {

SatClientImpl::SatClientImpl(std::shared_ptr<grpc::Channel> channel)
    : stub_(SATService::NewStub(channel)) {}

// Assembles the client's payload, sends it and presents the response back
// from the server.
SatResult SatClientImpl::RequestSAT(const clustersat::AndTerm& term, SatRequestIdentifier id) {
  // Data we are sening to the server.
  SatQuery query;
  *query.mutable_term() = term;
  SatRequest request;
  *request.mutable_query() = query;
  *request.mutable_id() = id;

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

SatResult SatClientImpl::LookupSAT(const int id) {
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

std::vector<SatResult> SatClientImpl::ListSATResults() {
  CurrentSatResultsRequest request;

  // Container for the data we expect from the server.
  CurrentSatResultsResponse reply;

  // Context for the client. It could be used to convey extra information to
  // the server and/or tweak certain RPC behaviors.
  grpc::ClientContext context;

  // The actual RPC.
  grpc::Status status = stub_->GetCurrentSatResults(&context, request, &reply);



  // Act upon its status.
  if (status.ok()) {
    std::vector<SatResult> results;
    for(auto result : reply.results()) {
      results.push_back(result);
    }
    return results;
  } else {
    std::cout << status.error_code() << ": " << status.error_message()
              << std::endl; 
    return std::vector<SatResult>();
  }
}
} // namespace clustersat