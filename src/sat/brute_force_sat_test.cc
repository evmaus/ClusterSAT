#include "src/sat/brute_force_sat.h"

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

TEST(BruteForceSatTest, FindsSatAnswerForSimpleSat) {
  Variable v("variable_name");
  auto not_v = UnaryOp::Not(v);
  auto t = Atom::True();
  auto expr = BinaryOp::And(t, not_v);
  BruteForceSatStrategy strategy(100000);
  EXPECT_EQ(strategy.DetermineSat(expr), SatResultType::SAT);
}

TEST(BruteForceSatTest, FindsSatAnswerForSimpleSatSecond) {
  Variable v("variable_name");
  auto t = Atom::True();
  auto expr = BinaryOp::And(t, v);
  BruteForceSatStrategy strategy(100000);
  EXPECT_EQ(strategy.DetermineSat(expr), SatResultType::SAT);
}

TEST(BruteForceSatTest, FindsUnsatAnswerForSimpleUnsat) {
  Variable v("variable_name");
  auto not_v = UnaryOp::Not(v);
  auto expr = BinaryOp::And(v, not_v);
  BruteForceSatStrategy strategy(100000);
  EXPECT_EQ(strategy.DetermineSat(expr), SatResultType::UNSAT);
}

TEST(BruteForceSatTest, FindsSatAnswerForMultivariateSat) {
  Variable v1("variable_name1");
  Variable v2("variable_name2");
  auto expr = BinaryOp::And(v1, v2);
  BruteForceSatStrategy strategy(100000);
  EXPECT_EQ(strategy.DetermineSat(expr), SatResultType::SAT);
}

TEST(BruteForceSatTest, TimeoutTest) {
  Variable v1("variable_name1");
  Variable v2("variable_name2");
  auto expr = new BinaryOp(BinaryType::AND, v1, v2);

  for (int i = 0; i < 1000; i++)
  {
    Variable* v3 = new Variable("variable_name"+std::to_string(i));
    expr = new BinaryOp(BinaryType::AND, *expr, *v3);
  }
  BruteForceSatStrategy strategy(1);
  EXPECT_EQ(strategy.DetermineSat(*expr), SatResultType::UNKNOWN);
}

} // namespace
} // namespace test
} // namespace tribblesat