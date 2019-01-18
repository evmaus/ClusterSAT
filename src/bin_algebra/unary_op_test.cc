#include "src/bin_algebra/unary_op.h"

#include "src/bin_algebra/atom.h"
#include "src/bin_algebra/variable.h"
#include "googletest/include/gtest/gtest.h"

namespace tribblesat {
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
} // namespace tribblesat