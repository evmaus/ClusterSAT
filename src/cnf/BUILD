cc_library(
  name = "cnf_variable_environment",
  srcs = [ "cnf_variable_environment.cc" ],
  hdrs = [ "cnf_variable_environment.h" ],
  deps = [ "//src/common:log" ],
  visibility = [ "//visibility:public" ],
)

cc_library(
  name = "cnf_vector_environment",
  srcs = [ "cnf_vector_environment.cc" ],
  hdrs = [ "cnf_vector_environment.h" ],
  deps = [ "cnf_variable_environment" ],
  visibility = [ "//visibility:public" ],
)

cc_test(
  name = "cnf_vector_environment_test",
  srcs = [ "cnf_vector_environment_test.cc" ],
  deps = [
    "cnf_vector_environment",
    "@googletest//:gtest_main",
  ]
)

cc_library(
  name = "cnf_and",
  srcs = [ "cnf_and_op.cc" ],
  hdrs = [ "cnf_and_op.h" ],
  deps = [
    "cnf_or",
    "cnf_variable_environment"
  ],
  visibility = [ "//visibility:public" ],
)

cc_test(
  name = "cnf_and_test",
  srcs = [ "cnf_and_op_test.cc" ],
  deps = [
    "cnf_and",
    "cnf_vector_environment",
    "@googletest//:gtest_main",
  ]
)

cc_library(
  name = "cnf_or",
  srcs = [ "cnf_or_op.cc" ],
  hdrs = [ "cnf_or_op.h" ],
  deps = [
    "cnf_variable",
    "cnf_variable_environment"
  ],
  visibility = [ "//visibility:public" ],
)

cc_test(
  name = "cnf_or_test",
  srcs = [ "cnf_or_op_test.cc" ],
  deps = [
    "cnf_or",
    "cnf_vector_environment",
    "@googletest//:gtest_main",
  ]
)

cc_library(
  name = "cnf_variable",
  srcs = [ "cnf_variable.cc" ],
  hdrs = [ "cnf_variable.h" ],
  deps = [ "cnf_variable_environment" ],
  visibility = [ "//visibility:public" ],
)

cc_test(
  name = "cnf_variable_test",
  srcs = [ "cnf_variable_test.cc" ],
  deps = [
    "cnf_variable",
    "cnf_vector_environment",
    "@googletest//:gtest_main",
  ]
)

cc_library(
  name = "cnf_environment_stack",
  srcs = [ "cnf_environment_stack.cc" ],
  hdrs = [ "cnf_environment_stack.h" ],
  deps = [ 
    "cnf_vector_environment",
    "cnf_variable_environment",
  ],
  visibility = [ "//visibility:public" ],
)

cc_test(
  name = "cnf_environment_stack_test",
  srcs = [ "cnf_environment_stack_test.cc" ],
  deps = [
    "cnf_environment_stack",
    "cnf_vector_environment",
    "@googletest//:gtest_main",
  ]
)