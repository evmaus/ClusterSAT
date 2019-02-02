#include "src/clustersat/client/sat_client.h"

#include <glog/logging.h>

namespace clustersat {

SatClientImpl::SatClientImpl(std::shared_ptr<grpc::Channel> channel)
    : stub_(SATService::NewStub(channel)) {}

// Assembles the client's payload, sends it and presents the response back
// from the server.
::util::StatusOr<SatResult> SatClientImpl::RequestSAT(const clustersat::AndTerm& term, SatRequestIdentifier id) {
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
    LOG(ERROR) << status.error_code() << ": " << status.error_message()
              << std::endl;
    return ::util::Status(::util::error::Code::UNKNOWN, status.error_message());
  }
}

::util::StatusOr<SatResult> SatClientImpl::LookupSAT(const int id) {
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
    LOG(ERROR) << status.error_code() << ": " << status.error_message()
              << std::endl;
    return ::util::Status(::util::error::Code::UNKNOWN, status.error_message());
  }
}

::util::StatusOr<std::vector<SatResult>> SatClientImpl::ListSATResults() {
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
    LOG(ERROR) << status.error_code() << ": " << status.error_message()
              << std::endl;
    return ::util::Status(::util::error::Code::UNKNOWN, status.error_message());
  }
}

::util::StatusOr<SatResult> SatClientImpl::CancelSAT(const int id) {
  // Data we are sening to the server.
  SatIdRequest request;
  request.mutable_id()->set_id(id);

  // Container for the data we expect from the server.
  SatResponse reply;

  // Context for the client. It could be used to convey extra information to
  // the server and/or tweak certain RPC behaviors.
  grpc::ClientContext context;

  // The actual RPC.
  grpc::Status status = stub_->CancelSatRequest(&context, request, &reply);

  // Act upon its status.
  if (status.ok()) {
    return reply.result();
  } else {
    LOG(ERROR) << status.error_code() << ": " << status.error_message()
              << std::endl;
    return ::util::Status(::util::error::Code::UNKNOWN, status.error_message());
  }
}

} // namespace clustersat