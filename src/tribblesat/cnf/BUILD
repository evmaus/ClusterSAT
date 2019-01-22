
cc_library(
  name = "cnf_and",
  srcs = [ "cnf_and_op.cc" ],
  hdrs = [ "cnf_and_op.h" ],
  deps = [
    "cnf_or",
    "//src/tribblesat/variable_environment:variable_environment"
  ],
  visibility = [ "//visibility:public" ],
)

cc_test(
  name = "cnf_and_test",
  srcs = [ "cnf_and_op_test.cc" ],
  deps = [
    "cnf_and",
    "//src/tribblesat/variable_environment:vector_environment",
    "@googletest//:gtest_main",
  ]
)

cc_library(
  name = "cnf_or",
  srcs = [ "cnf_or_op.cc" ],
  hdrs = [ "cnf_or_op.h" ],
  deps = [
    "cnf_variable",
    "//src/tribblesat/variable_environment:variable_environment"
  ],
  visibility = [ "//visibility:public" ],
)

cc_test(
  name = "cnf_or_test",
  srcs = [ "cnf_or_op_test.cc" ],
  deps = [
    "cnf_or",
    "//src/tribblesat/variable_environment:vector_environment",
    "@googletest//:gtest_main",
  ]
)

cc_library(
  name = "cnf_variable",
  srcs = [ "cnf_variable.cc" ],
  hdrs = [ "cnf_variable.h" ],
  deps = [ "//src/tribblesat/variable_environment:variable_environment" ],
  visibility = [ "//visibility:public" ],
)

cc_test(
  name = "cnf_variable_test",
  srcs = [ "cnf_variable_test.cc" ],
  deps = [
    "cnf_variable",
    "//src/tribblesat/variable_environment:vector_environment",
    "@googletest//:gtest_main",
  ]
)
