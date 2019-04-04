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


#include "src/simplesat/parsers/dimacs_parser.h"

#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <glob.h>

#include "googletest/include/gtest/gtest.h"
#include "src/simplesat/common/utilities.h"

namespace simplesat {
namespace test {
namespace 
{

constexpr char sat_testdata_directory[] = "src/simplesat/parsers/testdata/sat/*.cnf";

// Tests to make sure we can parse test files without crashing.
TEST(DiMacsParserTest, ParsesSimpleExampleCorrectly) {
  auto files = file_glob(sat_testdata_directory);
  for(auto filepath : files){
    std::ifstream file(filepath);
    DiMacsParser parser;
    auto parsed = parser.ParseCnf(file);
  }
}

} // namespace
} // namespace test
} // namespace simplesat