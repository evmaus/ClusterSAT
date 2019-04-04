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

#include "src/simplesat/variable_environment/variable_environment.h"
#include "src/simplesat/variable_environment/environment_stack.h"
#include "src/simplesat/variable_environment/linear_variable_selector.h"
#include "googletest/include/gtest/gtest.h"
#include "absl/memory/memory.h"

namespace simplesat {
namespace test {
namespace {

TEST(CnfVariableEnvironmentStack, CnfVariableEnvironmentRoundTripTest) {
  std::unique_ptr<VariableSelector> selector = absl::make_unique<LinearVariableSelector>(3);
  VariableEnvironmentStack stack(3, selector);
  stack.push();
  stack.assign(0, VariableState::STRUE);
  stack.assign(1, VariableState::SFALSE);
  stack.assign(2, VariableState::SUNBOUND);

  EXPECT_EQ(stack.lookup(0), VariableState::STRUE);
  EXPECT_EQ(stack.lookup(1), VariableState::SFALSE);
  EXPECT_EQ(stack.lookup(2), VariableState::SUNBOUND);
  EXPECT_EQ(stack.current_level(), 1);
  stack.pop();
  EXPECT_EQ(stack.current_level(), 0);

  EXPECT_EQ(stack.lookup(0), VariableState::SUNBOUND);
  EXPECT_EQ(stack.lookup(1), VariableState::SUNBOUND);
  EXPECT_EQ(stack.lookup(2), VariableState::SUNBOUND);
}

} // namespace
} // namespace test
} // namespace simplesat