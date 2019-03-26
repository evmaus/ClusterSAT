#include <fstream>
#include <iostream>

#include "gflags/gflags.h"
#include "src/simplesat/parsers/dimacs_parser.h"
#include "src/simplesat/bin_algebra/function.h"
#include <glog/logging.h>

DEFINE_string(file, "",
  "DIMACS Format file to pretty print");


int main(int argc, char** argv) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, true);

  std::ifstream file(FLAGS_file);
  simplesat::DiMacsParser parser;
  auto function = parser.ParseCnf(file);

  std::cout << function.to_string() << std::endl;
  return 0;
}