#include "src/sat/cdcl_sat.h"

#include <string>
#include <iostream>
#include <fstream>
#include <glob.h>

#include "googletest/include/gtest/gtest.h"
#include "src/parsers/dimacs_parser.h"
#include "src/common/log.h"
#include "src/common/utilities.h"

namespace tribblesat {
namespace test {
namespace {

constexpr char sat_testdata_directory[] = "src/sat/testdata/sat/*.cnf";
constexpr char unsat_testdata_directory[] = "src/sat/testdata/unsat/*.cnf";

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
  CDCLSatStrategy strategy(CDCLConfiguration(100000));
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
  CDCLSatStrategy strategy(CDCLConfiguration(100000));
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
  CDCLSatStrategy strategy(CDCLConfiguration(100000));
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
  CDCLSatStrategy strategy(CDCLConfiguration(1));
  EXPECT_EQ(strategy.DetermineCnfSat(expr).first, SatResultType::UNKNOWN);
}

TEST(CDCLSatTest, SATFilesLinearAssignment) {
  CDCLSatStrategy strategy(CDCLConfiguration(100000));
  std::vector<std::string> files = file_glob(sat_testdata_directory);
  EXPECT_GT(files.size(), 0);
  for(auto file_name : files){
    std::cout << file_name << std::endl;
    std::ifstream file(file_name);
    DiMacsParser parser;
    auto parsed = parser.ParseCnf(file);
    ASSERT_EQ(strategy.DetermineCnfSat(parsed).first, SatResultType::SAT);
  }
}

TEST(CDCLSatTest, UNSATFilesLinearAssignment) {
  CDCLSatStrategy strategy(CDCLConfiguration(100000));
  std::vector<std::string> files = file_glob(unsat_testdata_directory);
  EXPECT_GT(files.size(), 0);\
  for (int i = 0; i < 10; i++) {
    auto file_name = files[i];
    std::cout << file_name << std::endl;
    std::ifstream file(file_name);
    DiMacsParser parser;
    auto parsed = parser.ParseCnf(file);
    ASSERT_EQ(strategy.DetermineCnfSat(parsed).first, SatResultType::UNSAT);
  }
}

TEST(CDCLSatTest, SATFilesVSIDS) {
  CDCLSatStrategy strategy(CDCLConfiguration(100000, 
                            VariableSelectorType::VSIDS, 
                            CompactingPolicyType::TERM_SIZE, 
                            RestartPolicyType::GEOMETRIC));
  std::vector<std::string> files = file_glob(sat_testdata_directory);
  EXPECT_GT(files.size(), 0);
  for(auto file_name : files){
    std::cout << file_name << std::endl;
    std::ifstream file(file_name);
    DiMacsParser parser;
    auto parsed = parser.ParseCnf(file);
    ASSERT_EQ(strategy.DetermineCnfSat(parsed).first, SatResultType::SAT);
  }
}

TEST(CDCLSatTest, UNSATFilesVSIDS) {
  CDCLSatStrategy strategy(CDCLConfiguration(100000, 
                            VariableSelectorType::VSIDS, 
                            CompactingPolicyType::TERM_SIZE, 
                            RestartPolicyType::GEOMETRIC));
  std::vector<std::string> files = file_glob(unsat_testdata_directory);
  EXPECT_GT(files.size(), 0);\
  for (int i = 0; i < 10; i++) {
    auto file_name = files[i];
    std::cout << file_name << std::endl;
    std::ifstream file(file_name);
    DiMacsParser parser;
    auto parsed = parser.ParseCnf(file);
    ASSERT_EQ(strategy.DetermineCnfSat(parsed).first, SatResultType::UNSAT);
  }
}


} // namespace
} // namespace test
} // namespace tribblesat