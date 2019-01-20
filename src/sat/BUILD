cc_library(
    name = "sat_strategy",
    srcs = [ "sat_strategy.cc" ],
    hdrs = [ "sat_strategy.h" ],
    deps = [
        "//src/common:log",
        "//src/cnf:cnf_and",
        "//src/cnf:cnf_or",
        "//src/variable_environment:variable_environment",
        "//src/cnf:cnf_variable",
    ],
    visibility = [ "//visibility:public" ],
)

cc_library(
    name = "cdcl_trace",
    srcs = [ "cdcl_trace.cc" ],
    hdrs = [ "cdcl_trace.h" ],
    deps = [
        "clause_database",
        "//src/variable_environment:variable_environment",
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
        "cdcl_configuration",
        "clause_database",
        "//src/common:stats",
        "//src/variable_environment:linear_variable_selector",
        "//src/variable_environment:environment_stack",
    ],
    visibility = [ "//visibility:public" ],
)

cc_test(
    name = "cdcl_sat_test",
    srcs = [ "cdcl_sat_test.cc" ],
    deps = [
        "cdcl_sat",
        "//src/parsers:dimacs_parser",
        "//src/common:utilities",
        "@googletest//:gtest_main",
    ],
    data = glob(["testdata/**/*.cnf"]),
)

cc_library(
    name = "cdcl_configuration",
    srcs = [ "cdcl_configuration.cc" ],
    hdrs = [ "cdcl_configuration.h" ],
    deps = [
        "compacting_policy",
        "restart_policy",
        "//src/cnf:cnf_and",
        "//src/variable_environment:variable_selector",
        "//src/variable_environment:linear_variable_selector",
        "//src/variable_environment:vsids_variable_selector",
        "@com_google_absl//absl/memory",
    ],
    visibility = [ "//visibility:public" ],
)

cc_library(
    name = "clause_database",
    srcs = [ "clause_database.cc" ],
    hdrs = [ "clause_database.h" ],
    deps = [
        "compacting_policy",
        "//src/cnf:cnf_and",
        "//src/variable_environment:environment_stack",
    ]
)

cc_test(
    name = "clause_database_test",
    srcs = [ "clause_database_test.cc" ],
    deps = [
        "clause_database",
        "@googletest//:gtest_main",
    ]
)

cc_library(
    name = "compacting_policy",
    srcs = [ "compacting_policy.cc" ],
    hdrs = [ "compacting_policy.h" ],
    deps = [
        "//src/cnf:cnf_or",
    ]
)

cc_test(
    name = "compacting_policy_test",
    srcs = [ "compacting_policy_test.cc" ],
    deps = [
        "compacting_policy",
        "@googletest//:gtest_main",
    ]
)

cc_library(
    name = "restart_policy",
    srcs = [ "restart_policy.cc" ],
    hdrs = [ "restart_policy.h" ],
    deps = [
        "//src/common:stats",
        "//src/common:log"
    ],
)

cc_test(
    name = "restart_policy_test",
    srcs = [ "restart_policy_test.cc" ],
    deps = [
        "restart_policy",
        "@googletest//:gtest_main",
    ],
)