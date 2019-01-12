
cc_library(
    name = "function",
    srcs = ["function.cc"],
    hdrs = ["function.h"],
    deps = [
        "variable_environment",
    ]
)
cc_library(
    name = "variable",
    srcs = [ "variable.cc" ],
    hdrs = [ "variable.h" ],
    deps = [
        "function"
    ]
)

cc_test(
    name = "variable_test",
    srcs = ["variable_test.cc"],
    deps = [
        "variable",
        "@googletest//:gtest_main"
    ],
)

cc_library(
    name = "variable_environment",
    srcs = [ "variable_environment.cc" ],
    hdrs = [ "variable_environment.h" ],
    deps = [
    ]
)

cc_test(
    name = "variable_environment_test",
    srcs = ["variable_environment_test.cc"],
    deps = [
        "variable_environment",
        "@googletest//:gtest_main"
    ],
)

cc_library(
    name = "atom",
    srcs = [ "atom.cc" ],
    hdrs = [ "atom.h" ],
    deps = [
        "function"
    ]
)

cc_test(
    name = "atom_test",
    srcs = ["atom_test.cc"],
    deps = [
        "atom",
        "variable",
        "@googletest//:gtest_main"
    ],
)

cc_library(
    name = "unary_op",
    srcs = [ "unary_op.cc" ],
    hdrs = [ "unary_op.h" ],
    deps = [
        "function"
    ]
)

cc_test(
    name = "unary_op_test",
    srcs = ["unary_op_test.cc"],
    deps = [
        "unary_op",
        "atom",
        "variable",
        "@googletest//:gtest_main"
    ],
)


cc_library(
    name = "binary_op",
    srcs = [ "binary_op.cc" ],
    hdrs = [ "binary_op.h" ],
    deps = [
        "function"
    ]
)

cc_test(
    name = "binary_op_test",
    srcs = ["binary_op_test.cc"],
    deps = [
        "binary_op",
        "atom",
        "variable",
        "@googletest//:gtest_main"
    ],
)

cc_test(
    name = "integration",
    srcs = [ "model_integration_test.cc" ],
    deps = [
        "atom",
        "binary_op",
        "unary_op",
        "variable",
        "@googletest//:gtest_main",
    ]
)