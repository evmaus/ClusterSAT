cc_binary(
  name = "function_printer",
  srcs = [ "function_printer.cc" ],
  deps = [
    "//src/bin_algebra:function",
    "//src/parsers:dimacs_parser",
    "@com_google_gflags//:gflags"
  ]
)

cc_binary(
  name = "cdcl_runner",
  srcs = [ "cdcl_sat_runner.cc" ],
  deps = [
    "//src/common:log",
    "//src/sat:cdcl_sat",
    "//src/bin_algebra:function",
    "//src/parsers:dimacs_parser",
    "@com_google_gflags//:gflags"
  ]
)
