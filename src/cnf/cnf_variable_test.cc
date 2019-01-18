#include "src/cnf/cnf_variable.h"

#include "src/variable_environment/vector_environment.h"
#include "src/variable_environment/linear_variable_selector.h"
#include "googletest/include/gtest/gtest.h"

namespace tribblesat {
namespace cnf {
namespace {

TEST(VariableEnvironment, VariableEnvironmentRoundTripTest) {
  VectorVariableEnvironment env(3, LinearVariableSelector(3));

  env.assign(0, VariableState::STRUE);
  env.assign(1, VariableState::SFALSE);
  env.assign(2, VariableState::SUNBOUND);
  Variable v0(0);
  Variable v1(1);
  Variable v2(2);
  Variable nv0(0, true);
  Variable nv1(1, true);
  Variable nv2(2, true);
  EXPECT_EQ(v0.GetValueInEnvironment(env), VariableState::STRUE);
  EXPECT_EQ(v1.GetValueInEnvironment(env), VariableState::SFALSE);
  EXPECT_EQ(v2.GetValueInEnvironment(env), VariableState::SUNBOUND);
  
  EXPECT_EQ(nv0.GetValueInEnvironment(env), VariableState::SFALSE);
  EXPECT_EQ(nv1.GetValueInEnvironment(env), VariableState::STRUE);
  EXPECT_EQ(nv2.GetValueInEnvironment(env), VariableState::SUNBOUND);
}


} // namespace
} // namespace test
} // namespace tribblesat