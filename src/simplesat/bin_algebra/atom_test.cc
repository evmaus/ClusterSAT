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

#include "src/simplesat/bin_algebra/atom.h"

#include "googletest/include/gtest/gtest.h"

namespace simplesat {
namespace binary {
namespace test {
namespace {

TEST(AtomTest, TrueReturnsTrueAtom) {
  ASSERT_TRUE(Atom::True().Evaluate(VariableEnvironment::Empty()));
}

TEST(AtomTest, FalseReturnsFalseAtom) {
  ASSERT_FALSE(Atom::False().Evaluate(VariableEnvironment::Empty()));
}

TEST(AtomTest, HasNoUnboundVariables) {
  auto t = Atom::True();
  EXPECT_EQ(t.GetVariables().size(), 0);

  auto f = Atom::False();
  EXPECT_EQ(f.GetVariables().size(), 0);
}

} // namespace
} // namespace test
} // namespace binary
} // namespace simplesat