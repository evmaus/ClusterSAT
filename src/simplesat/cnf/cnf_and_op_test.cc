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

#include "src/simplesat/cnf/cnf_and_op.h"

#include "src/simplesat/variable_environment/linear_variable_selector.h"
#include "googletest/include/gtest/gtest.h"
#include "src/simplesat/variable_environment/vector_environment.h"

namespace simplesat {
namespace cnf {
namespace {

TEST(AndOpTest, SatisfiedTrue) {
  Variable v0(0);
  Variable v1(1);
  VectorVariableEnvironment env(2, LinearVariableSelector(2));
  env.assign(0, VariableState::SFALSE);
  env.assign(1, VariableState::STRUE);
  std::vector<Variable> vars;
  vars.push_back(v0);
  vars.push_back(v1);
  Or or_term(vars);
  std::list<Or> terms;
  terms.push_back(or_term);
  And and_term(terms);
  EXPECT_TRUE(and_term.satisfied(env));
}

TEST(AndOpTest, SatisfiedFalse) {
  Variable v0(0);
  Variable v1(1);
  VectorVariableEnvironment env(2, LinearVariableSelector(2));
  env.assign(0, VariableState::SFALSE);
  env.assign(1, VariableState::SFALSE);
  std::vector<Variable> vars;
  vars.push_back(v0);
  vars.push_back(v1);
  Or or_term(vars);
  std::list<Or> terms;
  terms.push_back(or_term);
  And and_term(terms);
  EXPECT_FALSE(and_term.satisfied(env));
}

TEST(AndOpTest, VariableCount_ReturnsExpected) {
  Variable v1(1);
  Variable v2(2);
  std::vector<Variable> vars;
  vars.push_back(v1);
  vars.push_back(v2);
  Or or_term(vars);
  std::list<Or> terms;
  terms.push_back(or_term);
  And and_term(terms);
  EXPECT_EQ(and_term.variable_count(), 2);
}

TEST(AndOpTest, HasUnit_True) {
  Variable v0(0);
  Variable v1(1);
  VectorVariableEnvironment env(2, LinearVariableSelector(2));
  env.assign(0, VariableState::SFALSE);
  env.assign(1, VariableState::SUNBOUND);
  std::vector<Variable> vars;
  vars.push_back(v0);
  vars.push_back(v1);
  Or or_term(vars);
  std::list<Or> terms;
  terms.push_back(or_term);
  And and_term(terms);
  EXPECT_TRUE(and_term.has_unit(env));
}

TEST(AndOpTest, HasUnit_False) {
  Variable v0(0);
  Variable v1(1);
  VectorVariableEnvironment env(2, LinearVariableSelector(2));
  env.assign(0, VariableState::SUNBOUND);
  env.assign(1, VariableState::SUNBOUND);
  std::vector<Variable> vars;
  vars.push_back(v0);
  vars.push_back(v1);
  Or or_term(vars);
  std::list<Or> terms;
  terms.push_back(or_term);
  And and_term(terms);
  EXPECT_FALSE(and_term.has_unit(env));
}

TEST(AndOpTest, NextUnit) {
  Variable v0(0);
  Variable v1(1);
  VectorVariableEnvironment env(2, LinearVariableSelector(2));
  env.assign(0, VariableState::SFALSE);
  env.assign(1, VariableState::SUNBOUND);
  std::vector<Variable> vars;
  vars.push_back(v0);
  vars.push_back(v1);
  Or or_term(vars);
  std::list<Or> terms;
  terms.push_back(or_term);
  And and_term(terms);
  EXPECT_EQ(and_term.unit_terms(env).front()->first_unassigned(env).id(), 1);
}

} // namespace
} // namespace test
} // namespace simplesat