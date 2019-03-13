#include <fstream>
#include <iostream>

#include <glog/logging.h>
#include "gflags/gflags.h"
#include "src/tribblesat/parsers/dimacs_parser.h"
#include "src/tribblesat/bin_algebra/function.h"
#include "src/tribblesat/sat/cdcl_sat.h"

DEFINE_string(file, "",
  "DIMACS Format file to CDCL SAT on");

int main(int argc, char** argv) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, true);

  std::ifstream file(FLAGS_file);
  tribblesat::DiMacsParser parser;
  auto function = parser.ParseCnf(file);

  tribblesat::CDCLConfiguration config(30000000, 
    tribblesat::VariableSelectorType::VSIDS, 
    tribblesat::CompactingPolicyType::TERM_SIZE,
    tribblesat::RestartPolicyType::GEOMETRIC);
  // timeout of 6 minutes.
  tribblesat::CDCLSatStrategy strategy(config);

  auto sat = strategy.DetermineCnfSat(function);

  switch(sat.first) {
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