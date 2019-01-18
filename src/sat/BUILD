cc_library(
    name = "brute_sat",
    srcs = [ "brute_force_sat.cc" ],
    hdrs = [ "brute_force_sat.h" ],
    deps = [
        "sat_strategy",
        "//src/cnf:cnf_vector_environment",
    ],
    visibility = [ "//visibility:public" ],
)

cc_test(
    name = "brute_sat_test",
    srcs = [ "brute_force_sat_test.cc" ],
    deps = [
        "brute_sat",
        "@googletest//:gtest_main",
    ],
)

cc_library(
    name = "sat_strategy",
    srcs = [ "sat_strategy.cc" ],
    hdrs = [ "sat_strategy.h" ],
    deps = [
        "//src/common:log",
        "//src/cnf:cnf_and",
        "//src/cnf:cnf_or",
        "//src/cnf:cnf_variable_environment",
        "//src/cnf:cnf_variable",
    ],
    visibility = [ "//visibility:public" ],
)


cc_library(
    name = "dpll_sat",
    srcs = [ "dpll_sat.cc" ],
    hdrs = [ "dpll_sat.h" ],
    deps = [
        "sat_strategy",
        "//src/cnf:cnf_vector_environment",
    ],
    visibility = [ "//visibility:public" ],
)

cc_test(
    name = "dpll_sat_test",
    srcs = [ "dpll_sat_test.cc" ],
    deps = [
        "dpll_sat",
        "//src/parsers:dimacs_parser",
        "@googletest//:gtest_main",
    ],
    data = glob(["testdata/*.cnf"]),
)

cc_library(
    name = "cdcl_trace",
    srcs = [ "cdcl_trace.cc" ],
    hdrs = [ "cdcl_trace.h" ],
    deps = [ 
        "//src/cnf:cnf_variable_environment",
        "//src/cnf:cnf_or",
        "//src/cnf:cnf_and",
    ],
)

cc_test(
    name = "cdcl_trace_test",
    srcs = [ "cdcl_trace_test.cc" ],
    deps = [ 
        "cdcl_trace",
        "@googletest//:gtest_main",
    ],
)

cc_library(
    name = "cdcl_sat",
    srcs = [ "cdcl_sat.cc" ],
    hdrs = [ "cdcl_sat.h" ],
    deps = [
        "sat_strategy",
        "cdcl_trace",
        "//src/cnf:cnf_vector_environment",
        "//src/cnf:cnf_environment_stack",
    ],
    visibility = [ "//visibility:public" ],
)

cc_test(
    name = "cdcl_sat_test",
    srcs = [ "cdcl_sat_test.cc" ],
    deps = [
        "cdcl_sat",
        "//src/parsers:dimacs_parser",
        "@googletest//:gtest_main",
    ],
    data = glob(["testdata/*.cnf"]),
)