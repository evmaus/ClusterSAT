#include <fstream>
#include <iostream>

#include "gflags/gflags.h"
#include "src/tribblesat/parsers/dimacs_parser.h"
#include "src/tribblesat/bin_algebra/function.h"
#include "src/tribblesat/common/log.h"

DEFINE_string(file, "",
  "DIMACS Format file to pretty print");


int main(int argc, char** argv) {
  gflags::ParseCommandLineFlags(&argc, &argv, true);

  tribblesat::SET_LOG_LEVEL(tribblesat::LogLevel::VERBOSE);

  std::ifstream file(FLAGS_file);
  tribblesat::DiMacsParser parser;
  auto function = parser.ParseCnf(file);

  std::cout << function.to_string() << std::endl;
  return 0;
}