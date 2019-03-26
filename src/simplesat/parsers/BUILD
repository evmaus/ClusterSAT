cc_library(
    name = "dimacs_parser",
    srcs = [ "dimacs_parser.cc" ],
    hdrs = [ "dimacs_parser.h" ],
    deps = [
        "//src/simplesat/cnf:cnf_and",
        "//src/simplesat/cnf:cnf_or",
        "//src/simplesat/variable_environment:variable_environment",
        "//src/simplesat/cnf:cnf_variable",
        "@com_google_absl//absl/strings",
    ],
    visibility = ["//visibility:public"]
)

cc_test(
    name = "dimacs_parser_test",
    srcs = [ "dimacs_parser_test.cc" ],
    deps = [
        "dimacs_parser",
        "//src/simplesat/cnf:cnf_and",
        "//src/simplesat/cnf:cnf_or",
        "//src/simplesat/variable_environment:variable_environment",
        "//src/simplesat/cnf:cnf_variable",
        "//src/simplesat/common:utilities",
        "@googletest//:gtest_main",
    ],
    data = glob(["testdata/**/*.cnf"]),
)