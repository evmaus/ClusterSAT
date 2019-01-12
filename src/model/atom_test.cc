#include "src/model/atom.h"
#include <gtest/gtest.h>

namespace tribblesat {
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
  EXPECT_EQ(t.GetUnboundVariables().size(), 0);

  auto f = Atom::False();
  EXPECT_EQ(f.GetUnboundVariables().size(), 0);
}

} // namespace
} // namespace test
} // namespace tribblesat