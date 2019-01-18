#include "src/variable_environment/vector_environment.h"
#include "src/variable_environment/linear_variable_selector.h"
#include "googletest/include/gtest/gtest.h"

namespace tribblesat {
namespace test {
namespace {

TEST(CnfVariableEnvironment, CnfVariableEnvironmentRoundTripTest) {
  variable_id count = 3;
  VectorVariableEnvironment env(count, LinearVariableSelector(count));

  env.assign(0, VariableState::STRUE);
  env.assign(1, VariableState::SFALSE);
  env.assign(2, VariableState::SUNBOUND);

  EXPECT_EQ(env.lookup(0), VariableState::STRUE);
  EXPECT_EQ(env.lookup(1), VariableState::SFALSE);
  EXPECT_EQ(env.lookup(2), VariableState::SUNBOUND);
  EXPECT_EQ(env.lookup(3), VariableState::SUNBOUND);
}


} // namespace
} // namespace test
} // namespace tribblesat