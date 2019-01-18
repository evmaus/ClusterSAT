
#include "src/parsers/dimacs_parser.h"

#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <filesystem>
#include "src/sat/brute_force_sat.h"
#include "googletest/include/gtest/gtest.h"

namespace tribblesat {
namespace test {
namespace 
{

constexpr char sat_testdata_directory[] = "src/parsers/testdata/";

// Tests to make sure we can parse test files without crashing.
TEST(DiMacsParserTest, ParsesSimpleExampleCorrectly) {
  

  for(int i = 0; i < kTest_file_count; i++) {
    std::ifstream file(sat_testdata[i]);
    DiMacsParser parser;
    auto parsed = parser.ParseCnf(file);
  }
}


} // namespace
} // namespace test
} // namespace tribblesat