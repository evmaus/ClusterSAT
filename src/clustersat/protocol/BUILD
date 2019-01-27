load("@com_github_grpc_grpc//bazel:grpc_build_system.bzl", "grpc_proto_library")

package(default_visibility = ["//visibility:public"])

grpc_proto_library(
  name = "clustersat_proto",
  srcs = ["clustersat.proto"],
  deps = [ "cnf_proto" ],
)

grpc_proto_library(
  name = "cnf_proto",
  srcs = ["cnf.proto"],
)
