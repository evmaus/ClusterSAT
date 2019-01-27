
cc_binary(
  name = "sat_client",
  srcs = ["sat_client.cc"],
  deps = [
    "//src/clustersat/protocol:clustersat_proto",
    "//src/clustersat/utilities:dimacs_parser",
    "@com_google_gflags//:gflags",
    "@com_github_grpc_grpc//:grpc++",
  ],
)