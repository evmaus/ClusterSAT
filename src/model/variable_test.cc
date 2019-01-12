#include "src/model/variable.h"

#include "src/model/variable_environment.h"

#include <string>
#include <gtest/gtest.h>


namespace tribblesat {
namespace test {
namespace {

TEST(VariableTest, RetrievesStoredTrueValue) {
  std::string variable_name = "test1";
  VariableEnvironment env = VariableEnvironment::Empty();
  env.Assign(variable_name, true);
  Variable v(variable_name);
  EXPECT_TRUE(v.Evaluate(env));
}

TEST(VariableTest, RetrievesStoredFalseValue) {
  std::string variable_name = "test1";
  VariableEnvironment env = VariableEnvironment::Empty();
  env.Assign(variable_name, false);
  Variable v(variable_name);
  EXPECT_FALSE(v.Evaluate(env));
}

TEST(VariableTest, UnboundVariablesReturnsSelf) {
  std::string variable_name = "test1";
  Variable v(variable_name);

  auto variables = v.GetUnboundVariables();
  ASSERT_EQ(variables.size(), 1);
  EXPECT_EQ(variables.at(0), "test1");
}

}
} // namespace test
} // namespace tribblesat