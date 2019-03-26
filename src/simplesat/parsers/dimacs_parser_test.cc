
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