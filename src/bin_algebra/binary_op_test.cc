#include "src/bin_algebra/binary_op.h"

#include "src/bin_algebra/atom.h"
#include "src/bin_algebra/variable.h"
#include "googletest/include/gtest/gtest.h"

namespace tribblesat {
namespace binary {
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

TEST(BinaryTest, IFFReturnsExpectedValues) {
  auto t = Atom::True();
  auto f = Atom::False();
  EXPECT_TRUE(BinaryOp::IFF(t, t).Evaluate(VariableEnvironment::Empty()));
  EXPECT_FALSE(BinaryOp::IFF(f, t).Evaluate(VariableEnvironment::Empty()));
  EXPECT_FALSE(BinaryOp::IFF(t, f).Evaluate(VariableEnvironment::Empty()));
  EXPECT_TRUE(BinaryOp::IFF(f, f).Evaluate(VariableEnvironment::Empty()));
}

TEST(BinaryTest, ImpliesReturnsExpectedValues) {
  auto t = Atom::True();
  auto f = Atom::False();
  EXPECT_TRUE(BinaryOp::Implies(t, t).Evaluate(VariableEnvironment::Empty()));
  EXPECT_TRUE(BinaryOp::Implies(f, t).Evaluate(VariableEnvironment::Empty()));
  EXPECT_FALSE(BinaryOp::Implies(t, f).Evaluate(VariableEnvironment::Empty()));
  EXPECT_TRUE(BinaryOp::Implies(f, f).Evaluate(VariableEnvironment::Empty()));
}

TEST(UnaryTest, GetVariableReturnsInternal) {
  std::string variable_name1 = "test1";
  std::string variable_name2 = "test2";
  Variable v1(variable_name1);
  Variable v2(variable_name2);
  auto expr = BinaryOp::And(v1, v2);

  auto variables = expr.GetVariables();
  ASSERT_EQ(variables.size(), 2);
}

} // namespace
} // namespace test
} // namespace binary
} // namespace tribblesat