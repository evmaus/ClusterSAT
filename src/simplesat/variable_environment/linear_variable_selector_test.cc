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

#include "src/simplesat/variable_environment/linear_variable_selector.h"
#include "googletest/include/gtest/gtest.h"

namespace simplesat {
namespace test {
namespace {

TEST(LinearVariableSelector, LinearVariableSelectorTest) {
  LinearVariableSelector selector(100);
  variable_id i = 1;
  for(auto it = selector.cbegin(); it != selector.cend(); it++) {
    EXPECT_EQ(i, *it);
    i++;
  }
}

} // namespace
} // namespace test
} // namespace simplesat