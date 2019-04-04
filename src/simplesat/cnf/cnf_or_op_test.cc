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

#include "src/simplesat/cnf/cnf_or_op.h"

#include <vector>

#include "src/simplesat/variable_environment/vector_environment.h"
#include "src/simplesat/variable_environment/linear_variable_selector.h"
#include "googletest/include/gtest/gtest.h"

namespace simplesat {
namespace cnf {
namespace {

TEST(CnfOrOp, GetTermState_TermIsSat) {
  Variable v0(0);
  Variable v1(1);
  VectorVariableEnvironment env(2, LinearVariableSelector(2));
  env.assign(0, VariableState::STRUE);
  env.assign(1, VariableState::SUNBOUND);
  std::vector<Variable> vars;
  vars.push_back(v0);
  vars.push_back(v1);
  Or or_term(vars);
  EXPECT_EQ(or_term.term_state(env), TermState::SAT);
}

TEST(CnfOrOp, GetTermState_TermIsUnsat) {

  Variable v0(0);
  Variable v1(1);
  VectorVariableEnvironment env(2, LinearVariableSelector(2));
  env.assign(0, VariableState::SFALSE);
  env.assign(1, VariableState::SFALSE);
  std::vector<Variable> vars;
  vars.push_back(v0);
  vars.push_back(v1);
  Or or_term(vars);
  EXPECT_EQ(or_term.term_state(env), TermState::UNSAT);
}

TEST(CnfOrOp, GetTermState_TermIsUnit) {
  Variable v0(0);
  Variable v1(1);
  VectorVariableEnvironment env(2, LinearVariableSelector(2));
  env.assign(0, VariableState::SFALSE);
  env.assign(1, VariableState::SUNBOUND);
  std::vector<Variable> vars;
  vars.push_back(v0);
  vars.push_back(v1);
  Or or_term(vars);
  EXPECT_EQ(or_term.term_state(env), TermState::UNIT);
}

TEST(CnfOrOp, GetTermState_TermIsUnresolved) {
  Variable v0(0);
  Variable v1(1);
  VectorVariableEnvironment env(2, LinearVariableSelector(2));
  env.assign(0, VariableState::SUNBOUND);
  env.assign(1, VariableState::SUNBOUND);
  std::vector<Variable> vars;
  vars.push_back(v0);
  vars.push_back(v1);
  Or or_term(vars);
  EXPECT_EQ(or_term.term_state(env), TermState::UNRESOLVED);
}

TEST(CnfOrOp, FirstUnassigned_AllAssigned){
  Variable v0(0);
  Variable v1(1);
  VectorVariableEnvironment env(2, LinearVariableSelector(2));
  env.assign(0, VariableState::STRUE);
  env.assign(1, VariableState::SFALSE);
  std::vector<Variable> vars;
  vars.push_back(v0);
  vars.push_back(v1);
  Or or_term(vars);
  EXPECT_EQ(or_term.first_unassigned(env).id(), 0);
}

TEST(CnfOrOp, FirstUnassigned){
  Variable v0(0);
  Variable v1(5);
  VectorVariableEnvironment env(5, LinearVariableSelector(2));
  env.assign(0, VariableState::STRUE);
  env.assign(5, VariableState::SUNBOUND);
  std::vector<Variable> vars;
  vars.push_back(v0);
  vars.push_back(v1);
  Or or_term(vars);
  EXPECT_EQ(or_term.first_unassigned(env).id(), 5);
}

} // namespace
} // namespace test
} // namespace simplesat