
#include "src/model/variable_environment.h"
#include "src/model/atom.h"
#include "src/model/binary_op.h"
#include "src/model/unary_op.h"
#include "src/model/variable.h"

#include <string>
#include <gtest/gtest.h>

namespace tribblesat {
namespace test {
namespace {

TEST(ModelIntegrationTest, VariableBinaryOp) {
  std::string variable_name = "test_variable";
  Variable v(variable_name);
  auto t = Atom::True();
  auto expr = BinaryOp::And(t, v);
  VariableEnvironment env1 = VariableEnvironment::Empty();
  env1.Assign(variable_name, true);
  EXPECT_TRUE(expr.Evaluate(env1));
  VariableEnvironment env2 = VariableEnvironment::Empty();
  env2.Assign(variable_name, false);
  EXPECT_FALSE(expr.Evaluate(env2));
}

TEST(ModelIntegrationTest, VariableUnaryOp) {
  std::string variable_name = "test_variable";
  Variable v(variable_name);
  auto expr = UnaryOp::Not(v);
  VariableEnvironment env1 = VariableEnvironment::Empty();
  env1.Assign(variable_name, true);
  EXPECT_FALSE(expr.Evaluate(env1));
  VariableEnvironment env2 = VariableEnvironment::Empty();
  env2.Assign(variable_name, false);
  EXPECT_TRUE(expr.Evaluate(env2));
}

TEST(ModelIntegrationTest, BigExprEvaluateTest) {
  std::string variable_name = "test_variable";
  Variable v(variable_name);
  auto not_v = UnaryOp::Not(v);
  auto f = Atom::False();

  auto expr = BinaryOp::Or(not_v, f);

  VariableEnvironment env1 = VariableEnvironment::Empty();
  env1.Assign(variable_name, true);
  EXPECT_FALSE(expr.Evaluate(env1));
  VariableEnvironment env2 = VariableEnvironment::Empty();
  env2.Assign(variable_name, false);
  EXPECT_TRUE(expr.Evaluate(env2));
}


TEST(ModelIntegrationTest, BigExprGetVariablesTest) {
  Variable v1("test_variable1");
  Variable v2("test_variable2");
  auto not_v = UnaryOp::Not(v1);
  auto f = Atom::False();
  auto not_v_or_f = BinaryOp::Or(not_v, f);
  auto expr = BinaryOp::And(not_v_or_f, v2);
  
  auto variables = expr.GetUnboundVariables();
  EXPECT_EQ(variables.size(), 2);
}


} // namespace
} // namespace test
} // namespace tribblesat