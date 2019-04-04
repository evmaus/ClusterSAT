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