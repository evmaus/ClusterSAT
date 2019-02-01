cc_binary(
  name = "leader_server",
  srcs = ["leader_server.cc"],
  deps = [
    ":leader",
    "//src/clustersat/protocol:clustersat_proto",
    "@com_google_glog//:glog",
    "@com_github_gflags_gflags//:gflags",
    "@com_github_grpc_grpc//:grpc++",
    "@com_google_absl//absl/strings",
  ],
)

cc_library (
  name = "leader",
  srcs = [ "leader.cc" ],
  hdrs = [ "leader.h" ],
  deps = [
    "//src/clustersat/client:sat_client",
    "//src/clustersat/protocol:clustersat_proto",
    "@com_github_grpc_grpc//:grpc++",
    "@com_google_glog//:glog",
  ],
)