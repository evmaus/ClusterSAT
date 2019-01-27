
cc_binary(
  name = "tribblesat_server",
  srcs = ["tribblesat_server.cc"],
  deps = [
    ":tribblesat_wrapper",
    "//src/tribblesat/sat:cdcl_sat",
    "//src/clustersat/protocol:clustersat_proto",
    "@com_github_grpc_grpc//:grpc++",
  ],
)

cc_library(
  name = "tribblesat_wrapper",
  srcs = ["tribblesat_wrapper.cc"],
  hdrs = ["tribblesat_wrapper.h"],
  deps = [
    "//src/tribblesat/sat:cdcl_sat",
    "//src/clustersat/protocol:clustersat_proto",
  ]
)

cc_library(
  name = "tribblesat_wrapper_test",
  srcs = ["tribblesat_wrapper_test.cc"],
  deps = [
    ":tribblesat_wrapper",
    "@googletest//:gtest_main",
  ]
)