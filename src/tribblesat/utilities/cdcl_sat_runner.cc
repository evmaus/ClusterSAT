#include <fstream>
#include <iostream>

#include "gflags/gflags.h"
#include "src/tribblesat/parsers/dimacs_parser.h"
#include "src/tribblesat/bin_algebra/function.h"
#include "src/tribblesat/sat/cdcl_sat.h"
#include "src/tribblesat/common/log.h"

DEFINE_string(file, "",
  "DIMACS Format file to CDCL SAT on");
DEFINE_bool(verbose, false, "Verbose output");
DEFINE_bool(info, false, "Informational output");

int main(int argc, char** argv) {
  gflags::ParseCommandLineFlags(&argc, &argv, true);

  if(FLAGS_info) {
    SET_LOG_LEVEL(tribblesat::LogLevel::INFORMATIONAL);
  }
  if(FLAGS_verbose) {
    SET_LOG_LEVEL(tribblesat::LogLevel::VERBOSE);
  }
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