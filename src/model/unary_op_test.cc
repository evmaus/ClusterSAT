#include "src/model/unary_op.h"

#include "src/model/atom.h"
#include "src/model/variable.h"
#include <gtest/gtest.h>

namespace tribblesat {
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

TEST(UnaryTest, GetUnboundVariableReturnsInternal) {
  std::string variable_name = "test1";
  Variable v(variable_name);
  auto expr = UnaryOp::Nop(v);

  auto variables = expr.GetUnboundVariables();
  ASSERT_EQ(variables.size(), 1);
  EXPECT_EQ(variables.at(0), "test1");
}

} // namespace
} // namespace test
} // namespace tribblesat