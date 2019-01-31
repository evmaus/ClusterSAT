
cc_binary(
  name = "sat_client_wrapper",
  srcs = ["sat_client_wrapper.cc"],
  deps = [
    ":sat_client",
    "//src/clustersat/protocol:clustersat_proto",
    "//src/clustersat/utilities:dimacs_parser",
    "@com_google_gflags//:gflags",
    "@com_github_grpc_grpc//:grpc++",
  ],
)

cc_library(
  name = "sat_client",
  srcs = ["sat_client.cc"],
  hdrs = ["sat_client.h"],
  deps = [
    "//src/clustersat/protocol:clustersat_proto",
    "@com_google_gflags//:gflags",
    "@com_github_grpc_grpc//:grpc++",
  ],
  visibility = ["//visibility:public" ],
)