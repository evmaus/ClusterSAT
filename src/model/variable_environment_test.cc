#include "src/model/variable_environment.h"
#include <gtest/gtest.h>

namespace tribblesat {
namespace test {
namespace {

TEST(VariableEnvironmentTest, AssignRoundtripWorksAsExpected)
{
  VariableEnvironment env = VariableEnvironment::Empty();
  std::string test1 = "test1";
  std::string test2 = "test2";
  env.Assign(test1, false);
  env.Assign(test2, true);
  EXPECT_FALSE(env.Lookup(test1));
  EXPECT_TRUE(env.Lookup(test2));
}

}
} // namespace test
} // namespace tribblesat