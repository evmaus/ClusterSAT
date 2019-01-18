#include <fstream>
#include <iostream>

#include "gflags/gflags.h"
#include "src/parsers/dimacs_parser.h"
#include "src/bin_algebra/function.h"
#include "src/sat/brute_force_sat.h"

DEFINE_string(file, "",
  "DIMACS Format file to brute force SAT on");


int main(int argc, char** argv) {
  gflags::ParseCommandLineFlags(&argc, &argv, true);

  std::ifstream file(FLAGS_file);
  tribblesat::DiMacsParser parser;
  auto function = parser.ParseCnf(file);

  // timeout of 6 minutes.
  tribblesat::BruteForceSatStrategy strategy(300000000);

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