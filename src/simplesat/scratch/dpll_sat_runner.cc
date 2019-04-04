// Copyright 2019 Google LLC
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

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