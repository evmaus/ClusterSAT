#include <fstream>
#include <iostream>

#include "gflags/gflags.h"
#include "src/parsers/dimacs_parser.h"
#include "src/bin_algebra/function.h"
#include "src/sat/cdcl_sat.h"
#include "src/common/log.h"

DEFINE_string(file, "",
  "DIMACS Format file to CDCL SAT on");
DEFINE_bool(verbose, false, "Verbose output");

int main(int argc, char** argv) {
  gflags::ParseCommandLineFlags(&argc, &argv, true);

  if(FLAGS_verbose) {
    SET_LOG_LEVEL(tribblesat::LogLevel::VERBOSE);
  }
  std::ifstream file(FLAGS_file);
  tribblesat::DiMacsParser parser;
  auto function = parser.ParseCnf(file);

  // timeout of 6 minutes.
  tribblesat::CDCLSatStrategy strategy(300000000);

  auto sat = strategy.DetermineCnfSat(function);

  switch(sat) {
    case tribblesat::SatResultType::SAT:
      std::cout << "SAT" << std::endl;
      break;
    case tribblesat::SatResultType::UNSAT:
      std::cout << "UNSAT" << std::endl;
      break;
    case tribblesat::SatResultType::UNKNOWN:
      std::cout << "UNKNOWN" << std::endl;
      break;
  }

  return 0;
}