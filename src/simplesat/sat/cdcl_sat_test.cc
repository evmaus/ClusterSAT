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

#include "src/simplesat/sat/cdcl_sat.h"

#include <string>
#include <iostream>
#include <fstream>
#include <glob.h>

#include "googletest/include/gtest/gtest.h"
#include "src/simplesat/parsers/dimacs_parser.h"
#include "src/simplesat/common/utilities.h"

namespace simplesat {
namespace test {
namespace {

constexpr char sat_testdata_directory[] = "src/simplesat/sat/testdata/sat/*.cnf";
constexpr char unsat_testdata_directory[] = "src/simplesat/sat/testdata/unsat/*.cnf";

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
  std::list<cnf::Or> conj;
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
  std::list<cnf::Or> conj;
  conj.push_back(term1);
  conj.push_back(term2);

  cnf::And expr(conj);
  CDCLSatStrategy strategy(CDCLConfiguration(100000));
  EXPECT_EQ(strategy.DetermineCnfSat(expr).first, SatResultType::UNSAT);
}

TEST(CDCLSatTest, Stress) {
  std::list<cnf::Or> terms;
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
  std::list<cnf::Or> terms;
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
} // namespace simplesat