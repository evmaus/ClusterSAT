#include "src/model/binary_op.h"

#include "src/model/atom.h"
#include "src/model/variable.h"
#include <gtest/gtest.h>

namespace tribblesat {
namespace test {
namespace {

TEST(BinaryTest, AndReturnsExpectedValues) {
  auto t = Atom::True();
  auto f = Atom::False();
  EXPECT_TRUE(BinaryOp::And(t, t).Evaluate(VariableEnvironment::Empty()));
  EXPECT_FALSE(BinaryOp::And(f, t).Evaluate(VariableEnvironment::Empty()));
  EXPECT_FALSE(BinaryOp::And(t, f).Evaluate(VariableEnvironment::Empty()));
  EXPECT_FALSE(BinaryOp::And(f, f).Evaluate(VariableEnvironment::Empty()));
}
TEST(BinaryTest, OrReturnsExpectedValues) {
  auto t = Atom::True();
  auto f = Atom::False();
  EXPECT_TRUE(BinaryOp::Or(t, t).Evaluate(VariableEnvironment::Empty()));
  EXPECT_TRUE(BinaryOp::Or(f, t).Evaluate(VariableEnvironment::Empty()));
  EXPECT_TRUE(BinaryOp::Or(t, f).Evaluate(VariableEnvironment::Empty()));
  EXPECT_FALSE(BinaryOp::Or(f, f).Evaluate(VariableEnvironment::Empty()));
}
TEST(BinaryTest, XorReturnsExpectedValues) {
  auto t = Atom::True();
  auto f = Atom::False();
  EXPECT_FALSE(BinaryOp::Xor(t, t).Evaluate(VariableEnvironment::Empty()));
  EXPECT_TRUE(BinaryOp::Xor(f, t).Evaluate(VariableEnvironment::Empty()));
  EXPECT_TRUE(BinaryOp::Xor(t, f).Evaluate(VariableEnvironment::Empty()));
  EXPECT_FALSE(BinaryOp::Xor(f, f).Evaluate(VariableEnvironment::Empty()));
}

TEST(UnaryTest, GetUnboundVariableReturnsInternal) {
  std::string variable_name1 = "test1";
  std::string variable_name2 = "test2";
  Variable v1(variable_name1);
  Variable v2(variable_name2);
  auto expr = BinaryOp::And(v1, v2);

  auto variables = expr.GetUnboundVariables();
  ASSERT_EQ(variables.size(), 2);
}

} // namespace
} // namespace test
} // namespace tribblesat