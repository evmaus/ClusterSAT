#include "src/sat/cdcl_sat.h"

#include <string>
#include <fstream>
#include <glob.h>

#include "googletest/include/gtest/gtest.h"
#include "src/parsers/dimacs_parser.h"
#include "src/common/log.h"

namespace tribblesat {
namespace test {
namespace {

constexpr int kTest_file_count = 2;
constexpr char sat_testdata_directory[] = "src/sat/testdata/sat/*.cnf";


TEST(CDCLSatTest, SatInstance){
  cnf::Variable v1(1);
  cnf::Variable v2(2);
  cnf::Variable v3(3);
  cnf::Variable nv3(3, true);
  cnf::Variable nv1(1, true);
  std::vector<cnf::Variable> t1;
  t1.push_back(v1);
  t1.push_back(nv3);
  cnf::Or term1(t1);
  std::vector<cnf::Variable> t2;
  t2.push_back(v2);
  t2.push_back(v3);
  t2.push_back(nv1);
  cnf::Or term2(t2);
  std::vector<cnf::Or> conj;
  conj.push_back(term1);
  conj.push_back(term2);


  cnf::And expr(conj);
  CDCLSatStrategy strategy(100000);
  EXPECT_EQ(strategy.DetermineCnfSat(expr).first, SatResultType::SAT);
}

TEST(CDCLSatTest, UnSatInstance){
  cnf::Variable v1(1);
  cnf::Variable nv1(1, true);
  std::vector<cnf::Variable> t1;
  t1.push_back(v1);
  cnf::Or term1(t1);
  std::vector<cnf::Variable> t2;
  t2.push_back(nv1);
  cnf::Or term2(t2);
  std::vector<cnf::Or> conj;
  conj.push_back(term1);
  conj.push_back(term2);

  cnf::And expr(conj);
  CDCLSatStrategy strategy(100000);
  EXPECT_EQ(strategy.DetermineCnfSat(expr).first, SatResultType::UNSAT);
}

TEST(CDCLSatTest, Stress) {
  std::vector<cnf::Or> terms;
  for (int i = 0; i < 50; i++)
  {
    cnf::Variable v(i);
    std::vector<cnf::Variable> vars;
    vars.push_back(v);
    cnf::Or term(vars);
    terms.push_back(term);
  }
  cnf::And expr(terms);
  CDCLSatStrategy strategy(1000000000);
  EXPECT_EQ(strategy.DetermineCnfSat(expr).first, SatResultType::SAT);
}

TEST(CDCLSatTest, Timeout) {
  std::vector<cnf::Or> terms;
  for (int i = 0; i < 1000; i++)
  {
    cnf::Variable v(i);
    std::vector<cnf::Variable> vars;
    vars.push_back(v);
    cnf::Or term(vars);
    terms.push_back(term);
  }
  cnf::And expr(terms);
  CDCLSatStrategy strategy(1);
  EXPECT_EQ(strategy.DetermineCnfSat(expr).first, SatResultType::UNKNOWN);
}

TEST(CDCLSatTest, Files) {
  SET_LOG_LEVEL(LogLevel::VERBOSE);
  CDCLSatStrategy strategy(1000000000);
  DiMacsParser parser;
  glob_t glob_result;
  glob(sat_testdata_directory,GLOB_TILDE,NULL,&glob_result);
  for(unsigned int i=0; i<glob_result.gl_pathc; ++i){
    std::ifstream file(glob_result.gl_pathv[i]);
    DiMacsParser parser;
    auto parsed = parser.ParseCnf(file);
    EXPECT_EQ(strategy.DetermineCnfSat(parsed).first, SatResultType::SAT);
  }
}

} // namespace
} // namespace test
} // namespace tribblesat