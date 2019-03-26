
load("@io_bazel_rules_docker//cc:image.bzl", "cc_image")

cc_image(
  name = "simplesat_docker",
  binary = ":simplesat_server",
)

cc_binary(
  name = "simplesat_server",
  srcs = ["simplesat_server.cc"],
  deps = [
    ":simplesat_wrapper",
    ":simplesat_server_impl",
    "//src/simplesat/sat:cdcl_sat",
    "//src/clustersat/protocol:clustersat_proto",
    "@com_google_glog//:glog",
    "@com_github_gflags_gflags//:gflags",
    "@com_github_grpc_grpc//:grpc++",
  ],
)

cc_library(
  name = "simplesat_wrapper",
  srcs = ["simplesat_wrapper.cc"],
  hdrs = ["simplesat_wrapper.h"],
  deps = [
    "//src/simplesat/sat:cdcl_sat",
    "//src/clustersat/protocol:clustersat_proto",
    "@com_google_glog//:glog",
  ]
)

cc_library(
  name = "simplesat_wrapper_test",
  srcs = ["simplesat_wrapper_test.cc"],
  deps = [
    ":simplesat_wrapper",
    "@googletest//:gtest_main",
  ]
)

cc_library(
  name = "simplesat_server_impl",
  srcs = [ "simplesat_server_impl.cc" ],
  hdrs = [ "simplesat_server_impl.h" ],
  deps = [
    ":simplesat_wrapper",
    "//src/simplesat/sat:cdcl_sat",
    "//src/clustersat/protocol:clustersat_proto",
    "@com_github_grpc_grpc//:grpc++",
  ]
)