#include "src/simplesat/variable_environment/variable_environment.h"
#include "src/simplesat/variable_environment/environment_stack.h"
#include "src/simplesat/variable_environment/linear_variable_selector.h"
#include "googletest/include/gtest/gtest.h"
#include "absl/memory/memory.h"

namespace simplesat {
namespace test {
namespace {

TEST(CnfVariableEnvironmentStack, CnfVariableEnvironmentRoundTripTest) {
  std::unique_ptr<VariableSelector> selector = absl::make_unique<LinearVariableSelector>(3);
  VariableEnvironmentStack stack(3, selector);
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
} // namespace simplesat