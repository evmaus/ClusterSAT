#include "src/cnf/cnf_variable.h"
#include "src/variable_environment/vector_environment.h"
#include "googletest/include/gtest/gtest.h"

namespace tribblesat {
namespace cnf {
namespace {

TEST(VariableEnvironment, VariableEnvironmentRoundTripTest) {
  VectorVariableEnvironment env(3);

  env.assign(0, cnf::VariableState::STRUE);
  env.assign(1, cnf::VariableState::SFALSE);
  env.assign(2, cnf::VariableState::SUNBOUND);
  Variable v0(0);
  Variable v1(1);
  Variable v2(2);
  Variable nv0(0, true);
  Variable nv1(1, true);
  Variable nv2(2, true);
  EXPECT_EQ(v0.GetValueInEnvironment(env), cnf::VariableState::STRUE);
  EXPECT_EQ(v1.GetValueInEnvironment(env), cnf::VariableState::SFALSE);
  EXPECT_EQ(v2.GetValueInEnvironment(env), cnf::VariableState::SUNBOUND);
  
  EXPECT_EQ(nv0.GetValueInEnvironment(env), cnf::VariableState::SFALSE);
  EXPECT_EQ(nv1.GetValueInEnvironment(env), cnf::VariableState::STRUE);
  EXPECT_EQ(nv2.GetValueInEnvironment(env), cnf::VariableState::SUNBOUND);
}


} // namespace
} // namespace test
} // namespace tribblesat