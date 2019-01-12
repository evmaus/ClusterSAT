
cc_library(
    name = "brute_sat",
    srcs = [ "brute_force_sat.cc" ],
    hdrs = [ "brute_force_sat.h" ],
    deps = [
        "sat_strategy",
        "//src/model:variable",
        "//src/model:function",
        "//src/model:binary_op",
        "//src/model:unary_op",
        "//src/model:atom",
    ]
)

cc_test(
    name = "brute_sat_test",
    srcs = [ "brute_force_sat_test.cc" ],
    deps = [
        "brute_sat",
        "//src/model:variable",
        "//src/model:function",
        "//src/model:binary_op",
        "//src/model:unary_op",
        "//src/model:atom",
        "@googletest//:gtest_main",
    ]
)

cc_library(
    name = "sat_strategy",
    srcs = [ "sat_strategy.cc" ],
    hdrs = [ "sat_strategy.h" ],
    deps = [
        "//src/model:function",
    ],
)