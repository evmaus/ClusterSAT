cc_binary(
  name = "function_printer",
  srcs = [ "function_printer.cc" ],
  deps = [
    "//src/tribblesat/bin_algebra:function",
    "//src/tribblesat/parsers:dimacs_parser",
    "@com_github_gflags_gflags//:gflags"
  ]
)

cc_binary(
  name = "cdcl_runner",
  srcs = [ "cdcl_sat_runner.cc" ],
  deps = [
    "//src/tribblesat/sat:cdcl_sat",
    "//src/tribblesat/bin_algebra:function",
    "//src/tribblesat/parsers:dimacs_parser",
    "@com_github_gflags_gflags//:gflags",  
    "@com_google_glog//:glog",
  ]
)
