
cc_binary(
  name = "sat_client_wrapper",
  srcs = ["sat_client_wrapper.cc"],
  deps = [
    ":sat_client",
    "//src/clustersat/protocol:clustersat_proto",
    "//src/clustersat/utilities:dimacs_parser",
    "@com_github_gflags_gflags//:gflags",
    "@com_github_grpc_grpc//:grpc++",
    "@com_google_glog//:glog",
  ],
)

cc_library(
  name = "sat_client",
  srcs = ["sat_client.cc"],
  hdrs = ["sat_client.h"],
  deps = [
    "//src/clustersat/protocol:clustersat_proto",
    "//src/utility/status:status",
    "@com_github_gflags_gflags//:gflags",
    "@com_github_grpc_grpc//:grpc++",
    "@com_google_glog//:glog",
  ],
  visibility = ["//visibility:public" ],
)

cc_binary(
  name = "timing_wrapper",
  srcs = ["timing_wrapper.cc"],
  deps = [
    ":sat_client",
    "//src/clustersat/protocol:clustersat_proto",
    "//src/clustersat/utilities:dimacs_parser",
    "@com_github_gflags_gflags//:gflags",
    "@com_github_grpc_grpc//:grpc++",
    "@com_google_glog//:glog",
  ],
)