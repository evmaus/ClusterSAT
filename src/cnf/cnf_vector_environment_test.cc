#include "src/cnf/cnf_vector_environment.h"
#include "googletest/include/gtest/gtest.h"

namespace tribblesat {
namespace cnf {
namespace {

TEST(CnfVariableEnvironment, CnfVariableEnvironmentRoundTripTest) {
  VectorVariableEnvironment env(3);

  env.assign(0, VariableState::STRUE);
  env.assign(1, VariableState::SFALSE);
  env.assign(2, VariableState::SUNBOUND);

  EXPECT_EQ(env.lookup(0), VariableState::STRUE);
  EXPECT_EQ(env.lookup(1), VariableState::SFALSE);
  EXPECT_EQ(env.lookup(2), VariableState::SUNBOUND);
}


} // namespace
} // namespace test
} // namespace tribblesat