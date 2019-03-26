cc_library(
  name = "variable_environment",
  srcs = [ "variable_environment.cc" ],
  hdrs = [ "variable_environment.h" ],
  deps = [ 
    "@com_google_glog//:glog",
  ],
  visibility = [ "//visibility:public" ],
)

cc_library(
  name = "vector_environment",
  srcs = [ "vector_environment.cc" ],
  hdrs = [ "vector_environment.h" ],
  deps = [ 
    "variable_environment",
    "variable_selector",
    "linear_variable_selector",
  ],
  visibility = [ "//visibility:public" ],
)

cc_test(
  name = "vector_environment_test",
  srcs = [ "vector_environment_test.cc" ],
  deps = [
    "vector_environment",
    "linear_variable_selector",
    "@googletest//:gtest_main",
  ]
)

cc_library(
  name = "environment_stack",
  srcs = [ "environment_stack.cc" ],
  hdrs = [ "environment_stack.h" ],
  deps = [ 
    "variable_environment",
    "variable_selector",
  ],
  visibility = [ "//visibility:public" ],
)

cc_test(
  name = "environment_stack_test",
  srcs = [ "environment_stack_test.cc" ],
  deps = [
    "environment_stack",
    "linear_variable_selector",
    "@com_google_absl//absl/memory",
    "@googletest//:gtest_main",
  ]
)


cc_library(
  name = "variable_selector",
  srcs = [ "variable_selector.cc" ],
  hdrs = [ "variable_selector.h" ],
  deps = [ 
    "variable_environment",
    "//src/simplesat/cnf:cnf_and",
    "//src/simplesat/common:stats",
    "@com_google_glog//:glog",
  ],
  visibility = [ "//visibility:public" ],
)

cc_library(
  name = "linear_variable_selector",
  srcs = [ "linear_variable_selector.cc" ],
  hdrs = [ "linear_variable_selector.h" ],
  deps = [ 
    "variable_selector",
    ],
  visibility = [ "//visibility:public" ],
)

cc_test(
  name = "linear_variable_selector_test",
  srcs = [ "linear_variable_selector_test.cc" ],
  deps = [
    "linear_variable_selector",
    "@googletest//:gtest_main",
  ]
)

cc_library(
  name = "vsids_variable_selector",
  srcs = [ "vsids_variable_selector.cc" ],
  hdrs = [ "vsids_variable_selector.h" ],
  deps = [ 
    "variable_selector",
    ],
  visibility = [ "//visibility:public" ],
)