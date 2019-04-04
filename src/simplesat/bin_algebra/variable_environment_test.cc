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

#include "src/simplesat/bin_algebra/variable_environment.h"

#include "googletest/include/gtest/gtest.h"

namespace simplesat {
namespace binary {
namespace test {
namespace {

TEST(VariableEnvironmentTest, AssignRoundtripWorksAsExpected)
{
  VariableEnvironment env = VariableEnvironment::Empty();
  std::string test1 = "test1";
  std::string test2 = "test2";
  env.Assign(test1, false);
  env.Assign(test2, true);
  EXPECT_FALSE(env.Lookup(test1));
  EXPECT_TRUE(env.Lookup(test2));
}

}
} // namespace test
} // namespace binary
} // namespace simplesat