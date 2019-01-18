#include "src/cnf/cnf_variable_environment.h"
#include "src/cnf/cnf_environment_stack.h"
#include "googletest/include/gtest/gtest.h"

namespace tribblesat {
namespace cnf {
namespace {

TEST(CnfVariableEnvironmentStack, CnfVariableEnvironmentRoundTripTest) {
  VariableEnvironmentStack stack(3);
  stack.push();
  stack.assign(0, VariableState::STRUE);
  stack.assign(1, VariableState::SFALSE);
  stack.assign(2, VariableState::SUNBOUND);

  EXPECT_EQ(stack.lookup(0), VariableState::STRUE);
  EXPECT_EQ(stack.lookup(1), VariableState::SFALSE);
  EXPECT_EQ(stack.lookup(2), VariableState::SUNBOUND);
  EXPECT_EQ(stack.current_level(), 1);
  stack.pop();
  EXPECT_EQ(stack.current_level(), 0);

  EXPECT_EQ(stack.lookup(0), VariableState::SUNBOUND);
  EXPECT_EQ(stack.lookup(1), VariableState::SUNBOUND);
  EXPECT_EQ(stack.lookup(2), VariableState::SUNBOUND);
}

} // namespace
} // namespace test
} // namespace tribblesat