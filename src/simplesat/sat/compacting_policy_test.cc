#include "src/simplesat/sat/compacting_policy.h"

#include "googletest/include/gtest/gtest.h"

namespace simplesat {
namespace test {
namespace {

TEST(TermSizeCompactingPolicyTest, InitWorksAsExpected) {
  // int compact_below_level, int term_size, int keep_terms
  TermSizeCompactingPolicy policy(0, 8, 50);
  ASSERT_EQ(policy.keep_last(), 50);
}

TEST(TermSizeCompactingPolicyTest, CompactLevelRespected) {
  // int compact_below_level, int term_size, int keep_terms
  TermSizeCompactingPolicy policy(2, 8, 50);
  ASSERT_TRUE(policy.should_compact(0));
  ASSERT_TRUE(policy.should_compact(2));
  ASSERT_FALSE(policy.should_compact(5));
}

TEST(TermSizeCompactingPolicyTest, CleanupWorksAsExpected) {
  // int compact_below_level, int term_size, int keep_terms
  TermSizeCompactingPolicy policy(2, 2, 50);
  cnf::Variable v0(0);
  cnf::Variable v1(1);
  cnf::Variable v2(2);
  std::vector<cnf::Variable> vars1;
  vars1.push_back(v0);
  vars1.push_back(v1);
  cnf::Or or_term1(vars1);
  std::vector<cnf::Variable> vars2;
  vars2.push_back(v0);
  vars2.push_back(v1);
  vars2.push_back(v2);
  cnf::Or or_term2(vars2);

  ASSERT_FALSE(policy.remove_term(1, or_term1));
  ASSERT_TRUE(policy.remove_term(1, or_term2));
}



} // namespace
} // namespace test
} // namespace simplesat