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

#include "src/sat/dpll_sat.h"
#include "src/parsers/dimacs_parser.h"

#include <string>
#include <fstream>
#include "googletest/include/gtest/gtest.h"
#include "src/common/log.h"

namespace tribblesat {
namespace test {
namespace {

constexpr int kTest_file_count = 2;
std::string sat_testdata[] = {
  "src/sat/testdata/sat/dimacs_parser_test_file.cnf", 
  "src/sat/testdata/sat/sample.cnf"
};

TEST(DPLLSatTest, SatInstance){
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
  DPLLSatStrategy strategy(100000);
  EXPECT_EQ(strategy.DetermineCnfSat(expr).first, SatResultType::SAT);
}

TEST(DPLLSatTest, UnSatInstance){
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
  DPLLSatStrategy strategy(100000);
  EXPECT_EQ(strategy.DetermineCnfSat(expr).first, SatResultType::UNSAT);
}

TEST(DPLLSatTest, Stress) {
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
  DPLLSatStrategy strategy(1000000000);
  EXPECT_EQ(strategy.DetermineCnfSat(expr).first, SatResultType::SAT);
}

TEST(DPLLSatTest, Timeout) {
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
  DPLLSatStrategy strategy(1);
  EXPECT_EQ(strategy.DetermineCnfSat(expr).first, SatResultType::UNKNOWN);
}


TEST(DPLLSatTest, Files) {
  DPLLSatStrategy strategy(1000000000);
  DiMacsParser parser;
  for (int i = 0; i < kTest_file_count; i++)
  {  
    std::ifstream file(sat_testdata[i]);
    auto expr = parser.ParseCnf(file);  
    EXPECT_EQ(strategy.DetermineCnfSat(expr).first, SatResultType::SAT);
  }
}

} // namespace
} // namespace test
} // namespace tribblesat