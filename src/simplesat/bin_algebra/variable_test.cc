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

#include "src/simplesat/bin_algebra/variable.h"

#include "src/simplesat/bin_algebra/variable_environment.h"

#include <string>
#include "googletest/include/gtest/gtest.h"


namespace simplesat {
namespace binary {
namespace test {
namespace {

TEST(VariableTest, RetrievesStoredTrueValue) {
  std::string variable_name = "test1";
  VariableEnvironment env = VariableEnvironment::Empty();
  env.Assign(variable_name, true);
  Variable v(variable_name);
  EXPECT_TRUE(v.Evaluate(env));
}

TEST(VariableTest, RetrievesStoredFalseValue) {
  std::string variable_name = "test1";
  VariableEnvironment env = VariableEnvironment::Empty();
  env.Assign(variable_name, false);
  Variable v(variable_name);
  EXPECT_FALSE(v.Evaluate(env));
}

TEST(VariableTest, VariablesReturnsSelf) {
  std::string variable_name = "test1";
  Variable v(variable_name);

  auto variables = v.GetVariables();
  ASSERT_EQ(variables.size(), 1);
  auto present = variables.find("test1") != variables.end();
  EXPECT_TRUE(present);
}

}
} // namespace test
} // namespace binary
} // namespace simplesat