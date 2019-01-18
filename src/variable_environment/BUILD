cc_library(
  name = "variable_environment",
  srcs = [ "variable_environment.cc" ],
  hdrs = [ "variable_environment.h" ],
  deps = [ "//src/common:log" ],
  visibility = [ "//visibility:public" ],
)

cc_library(
  name = "vector_environment",
  srcs = [ "vector_environment.cc" ],
  hdrs = [ "vector_environment.h" ],
  deps = [ "variable_environment" ],
  visibility = [ "//visibility:public" ],
)

cc_test(
  name = "vector_environment_test",
  srcs = [ "vector_environment_test.cc" ],
  deps = [
    "vector_environment",
    "@googletest//:gtest_main",
  ]
)

cc_library(
  name = "environment_stack",
  srcs = [ "environment_stack.cc" ],
  hdrs = [ "environment_stack.h" ],
  deps = [ 
    "vector_environment",
    "variable_environment",
  ],
  visibility = [ "//visibility:public" ],
)

cc_test(
  name = "environment_stack_test",
  srcs = [ "environment_stack_test.cc" ],
  deps = [
    "environment_stack",
    "vector_environment",
    "@googletest//:gtest_main",
  ]
)