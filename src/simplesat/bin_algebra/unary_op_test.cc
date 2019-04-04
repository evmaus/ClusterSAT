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

#include "src/simplesat/bin_algebra/unary_op.h"

#include "src/simplesat/bin_algebra/atom.h"
#include "src/simplesat/bin_algebra/variable.h"
#include "googletest/include/gtest/gtest.h"

namespace simplesat {
namespace binary {
namespace test {
namespace {

TEST(UnaryTest, NotTrueReturnsFalse) {
  auto t = Atom::True();
  ASSERT_FALSE(UnaryOp::Not(t).Evaluate(VariableEnvironment::Empty()));
}

TEST(UnaryTest, NotFalseReturnsTrue) {
  auto f = Atom::False();
  ASSERT_TRUE(UnaryOp::Not(f).Evaluate(VariableEnvironment::Empty()));
}

TEST(UnaryTest, NopTrueReturnsTrue) {
  auto t = Atom::True();
  ASSERT_TRUE(UnaryOp::Nop(t).Evaluate(VariableEnvironment::Empty()));
}

TEST(UnaryTest, NopFalseReturnsFalse) {
  auto f = Atom::False();
  ASSERT_FALSE(UnaryOp::Nop(f).Evaluate(VariableEnvironment::Empty()));
}

TEST(UnaryTest, GetVariableReturnsInternal) {
  std::string variable_name = "test1";
  Variable v(variable_name);
  auto expr = UnaryOp::Nop(v);

  auto variables = expr.GetVariables();
  ASSERT_EQ(variables.size(), 1);

  auto present = variables.find("test1") != variables.end();
  EXPECT_TRUE(present);
}

} // namespace
} // namespace test
} // namespace binary
} // namespace simplesat