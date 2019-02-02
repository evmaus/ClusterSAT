
load("@io_bazel_rules_docker//cc:image.bzl", "cc_image")

cc_image(
  name = "tribblesat_docker",
  binary = ":tribblesat_server",
)

cc_binary(
  name = "tribblesat_server",
  srcs = ["tribblesat_server.cc"],
  deps = [
    ":tribblesat_wrapper",
    ":tribblesat_server_impl",
    "//src/tribblesat/sat:cdcl_sat",
    "//src/clustersat/protocol:clustersat_proto",
    "@com_google_glog//:glog",
    "@com_github_gflags_gflags//:gflags",
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
    "@com_google_glog//:glog",
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

cc_library(
  name = "tribblesat_server_impl",
  srcs = [ "tribblesat_server_impl.cc" ],
  hdrs = [ "tribblesat_server_impl.h" ],
  deps = [
    ":tribblesat_wrapper",
    "//src/tribblesat/sat:cdcl_sat",
    "//src/clustersat/protocol:clustersat_proto",
    "@com_github_grpc_grpc//:grpc++",
  ]
)