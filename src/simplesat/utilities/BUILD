cc_binary(
  name = "function_printer",
  srcs = [ "function_printer.cc" ],
  deps = [
    "//src/simplesat/bin_algebra:function",
    "//src/simplesat/parsers:dimacs_parser",
    "@com_github_gflags_gflags//:gflags"
  ]
)

cc_binary(
  name = "cdcl_runner",
  srcs = [ "cdcl_sat_runner.cc" ],
  deps = [
    "//src/simplesat/sat:cdcl_sat",
    "//src/simplesat/bin_algebra:function",
    "//src/simplesat/parsers:dimacs_parser",
    "@com_github_gflags_gflags//:gflags",  
    "@com_google_glog//:glog",
  ]
)
