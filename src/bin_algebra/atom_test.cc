#include "src/bin_algebra/atom.h"

#include "googletest/include/gtest/gtest.h"

namespace tribblesat {
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
} // namespace tribblesat