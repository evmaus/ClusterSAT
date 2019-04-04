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

#include "src/simplesat/cnf/cnf_variable.h"

#include "src/simplesat/variable_environment/vector_environment.h"
#include "src/simplesat/variable_environment/linear_variable_selector.h"
#include "googletest/include/gtest/gtest.h"

namespace simplesat {
namespace cnf {
namespace {

TEST(VariableEnvironment, VariableEnvironmentRoundTripTest) {
  VectorVariableEnvironment env(3, LinearVariableSelector(3));

  env.assign(0, VariableState::STRUE);
  env.assign(1, VariableState::SFALSE);
  env.assign(2, VariableState::SUNBOUND);
  Variable v0(0);
  Variable v1(1);
  Variable v2(2);
  Variable nv0(0, true);
  Variable nv1(1, true);
  Variable nv2(2, true);
  EXPECT_EQ(v0.GetValueInEnvironment(env), VariableState::STRUE);
  EXPECT_EQ(v1.GetValueInEnvironment(env), VariableState::SFALSE);
  EXPECT_EQ(v2.GetValueInEnvironment(env), VariableState::SUNBOUND);
  
  EXPECT_EQ(nv0.GetValueInEnvironment(env), VariableState::SFALSE);
  EXPECT_EQ(nv1.GetValueInEnvironment(env), VariableState::STRUE);
  EXPECT_EQ(nv2.GetValueInEnvironment(env), VariableState::SUNBOUND);
}


} // namespace
} // namespace test
} // namespace simplesat