cc_binary(
  name = "leader_server",
  srcs = ["leader_server.cc"],
  deps = [
    ":leader",
    "//src/clustersat/protocol:clustersat_proto",
    "@com_github_grpc_grpc//:grpc++",
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
  ],
)