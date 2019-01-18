#include <fstream>
#include <iostream>

#include "gflags/gflags.h"
#include "src/parsers/dimacs_parser.h"
#include "src/bin_algebra/function.h"
#include "src/sat/dpll_sat.h"
#include "src/common/log.h"

DEFINE_string(file, "",
  "DIMACS Format file to DPLL SAT on");


int main(int argc, char** argv) {
  gflags::ParseCommandLineFlags(&argc, &argv, true);

  SET_LOG_LEVEL(tribblesat::LogLevel::VERBOSE);
  std::ifstream file(FLAGS_file);
  tribblesat::DiMacsParser parser;
  auto function = parser.ParseCnf(file);

  // timeout of 6 minutes.
  tribblesat::DPLLSatStrategy strategy(300000000);

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