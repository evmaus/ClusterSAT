#include "src/tribblesat/variable_environment/linear_variable_selector.h"
#include "googletest/include/gtest/gtest.h"

namespace tribblesat {
namespace test {
namespace {

TEST(LinearVariableSelector, LinearVariableSelectorTest) {
  LinearVariableSelector selector(100);
  variable_id i = 1;
  for(auto it = selector.cbegin(); it != selector.cend(); it++) {
    EXPECT_EQ(i, *it);
    i++;
  }
}

} // namespace
} // namespace test
} // namespace tribblesat