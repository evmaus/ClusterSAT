cc_library(
    name = "dimacs_parser",
    srcs = [ "dimacs_parser.cc" ],
    hdrs = [ "dimacs_parser.h" ],
    deps = [
        "//src/cnf:cnf_and",
        "//src/cnf:cnf_or",
        "//src/cnf:cnf_variable_environment",
        "//src/cnf:cnf_variable",
        "@com_google_absl//absl/strings",
    ],
    visibility = ["//visibility:public"]
)

cc_test(
    name = "dimacs_parser_test",
    srcs = [ "dimacs_parser_test.cc" ],
    deps = [
        "dimacs_parser",
        "//src/cnf:cnf_and",
        "//src/cnf:cnf_or",
        "//src/cnf:cnf_variable_environment",
        "//src/cnf:cnf_variable",
        "//src/sat:brute_sat",
        "@googletest//:gtest_main",
    ],
    data = glob(["testdata/*.cnf"]),
)