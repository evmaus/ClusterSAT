
#include "src/parsers/dimacs_parser.h"

#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <glob.h>

#include "src/sat/brute_force_sat.h"
#include "googletest/include/gtest/gtest.h"

namespace tribblesat {
namespace test {
namespace 
{

constexpr char sat_testdata_directory[] = "src/parsers/testdata/sat/*.cnf";

// Tests to make sure we can parse test files without crashing.
TEST(DiMacsParserTest, ParsesSimpleExampleCorrectly) {
  glob_t glob_result;
  glob(sat_testdata_directory,GLOB_TILDE,NULL,&glob_result);
  for(unsigned int i=0; i<glob_result.gl_pathc; ++i){
    std::ifstream file(glob_result.gl_pathv[i]);
    DiMacsParser parser;
    auto parsed = parser.ParseCnf(file);
  }
}

} // namespace
} // namespace test
} // namespace tribblesat