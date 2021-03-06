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

#include <glog/logging.h>
#include "gflags/gflags.h"
#include "src/simplesat/parsers/dimacs_parser.h"
#include "src/simplesat/bin_algebra/function.h"
#include "src/simplesat/sat/cdcl_sat.h"

DEFINE_string(file, "",
  "DIMACS Format file to CDCL SAT on");

int main(int argc, char** argv) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, true);

  std::ifstream file(FLAGS_file);
  simplesat::DiMacsParser parser;
  auto function = parser.ParseCnf(file);

  simplesat::CDCLConfiguration config(30000000, 
    simplesat::VariableSelectorType::VSIDS, 
    simplesat::CompactingPolicyType::TERM_SIZE,
    simplesat::RestartPolicyType::GEOMETRIC);
  // timeout of 6 minutes.
  simplesat::CDCLSatStrategy strategy(config);

  auto sat = strategy.DetermineCnfSat(function);

  switch(sat.first) {
    case simplesat::SatResultType::SAT:
      std::cout << "SAT" << std::endl;
      break;
    case simplesat::SatResultType::UNSAT:
      std::cout << "UNSAT" << std::endl;
      break;
    case simplesat::SatResultType::UNKNOWN:
      std::cout << "UNKNOWN" << std::endl;
      break;
  }

  return 0;
}