cc_library(
    name = "dimacs_parser",
    srcs = [ "dimacs_parser.cc" ],
    hdrs = [ "dimacs_parser.h" ],
    deps = [
        "//src/tribblesat/cnf:cnf_and",
        "//src/tribblesat/cnf:cnf_or",
        "//src/tribblesat/variable_environment:variable_environment",
        "//src/tribblesat/cnf:cnf_variable",
        "@com_google_absl//absl/strings",
    ],
    visibility = ["//visibility:public"]
)

cc_test(
    name = "dimacs_parser_test",
    srcs = [ "dimacs_parser_test.cc" ],
    deps = [
        "dimacs_parser",
        "//src/tribblesat/cnf:cnf_and",
        "//src/tribblesat/cnf:cnf_or",
        "//src/tribblesat/variable_environment:variable_environment",
        "//src/tribblesat/cnf:cnf_variable",
        "//src/tribblesat/common:utilities",
        "@googletest//:gtest_main",
    ],
    data = glob(["testdata/**/*.cnf"]),
)