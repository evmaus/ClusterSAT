#include "src/cnf/cnf_and_op.h"

#include "src/variable_environment/linear_variable_selector.h"
#include "googletest/include/gtest/gtest.h"
#include "src/variable_environment/vector_environment.h"

namespace tribblesat {
namespace cnf {
namespace {

TEST(AndOpTest, SatisfiedTrue) {
  Variable v0(0);
  Variable v1(1);
  VectorVariableEnvironment env(2, LinearVariableSelector(2));
  env.assign(0, VariableState::SFALSE);
  env.assign(1, VariableState::STRUE);
  std::vector<Variable> vars;
  vars.push_back(v0);
  vars.push_back(v1);
  Or or_term(vars);
  std::list<Or> terms;
  terms.push_back(or_term);
  And and_term(terms);
  EXPECT_TRUE(and_term.satisfied(env));
}

TEST(AndOpTest, SatisfiedFalse) {
  Variable v0(0);
  Variable v1(1);
  VectorVariableEnvironment env(2, LinearVariableSelector(2));
  env.assign(0, VariableState::SFALSE);
  env.assign(1, VariableState::SFALSE);
  std::vector<Variable> vars;
  vars.push_back(v0);
  vars.push_back(v1);
  Or or_term(vars);
  std::list<Or> terms;
  terms.push_back(or_term);
  And and_term(terms);
  EXPECT_FALSE(and_term.satisfied(env));
}

TEST(AndOpTest, VariableCount_ReturnsExpected) {
  Variable v1(1);
  Variable v2(2);
  std::vector<Variable> vars;
  vars.push_back(v1);
  vars.push_back(v2);
  Or or_term(vars);
  std::list<Or> terms;
  terms.push_back(or_term);
  And and_term(terms);
  EXPECT_EQ(and_term.variable_count(), 2);
}

TEST(AndOpTest, HasUnit_True) {
  Variable v0(0);
  Variable v1(1);
  VectorVariableEnvironment env(2, LinearVariableSelector(2));
  env.assign(0, VariableState::SFALSE);
  env.assign(1, VariableState::SUNBOUND);
  std::vector<Variable> vars;
  vars.push_back(v0);
  vars.push_back(v1);
  Or or_term(vars);
  std::list<Or> terms;
  terms.push_back(or_term);
  And and_term(terms);
  EXPECT_TRUE(and_term.has_unit(env));
}

TEST(AndOpTest, HasUnit_False) {
  Variable v0(0);
  Variable v1(1);
  VectorVariableEnvironment env(2, LinearVariableSelector(2));
  env.assign(0, VariableState::SUNBOUND);
  env.assign(1, VariableState::SUNBOUND);
  std::vector<Variable> vars;
  vars.push_back(v0);
  vars.push_back(v1);
  Or or_term(vars);
  std::list<Or> terms;
  terms.push_back(or_term);
  And and_term(terms);
  EXPECT_FALSE(and_term.has_unit(env));
}

TEST(AndOpTest, NextUnit) {
  Variable v0(0);
  Variable v1(1);
  VectorVariableEnvironment env(2, LinearVariableSelector(2));
  env.assign(0, VariableState::SFALSE);
  env.assign(1, VariableState::SUNBOUND);
  std::vector<Variable> vars;
  vars.push_back(v0);
  vars.push_back(v1);
  Or or_term(vars);
  std::list<Or> terms;
  terms.push_back(or_term);
  And and_term(terms);
  EXPECT_EQ(and_term.next_unit(env).first_unassigned(env).id(), 1);
}

} // namespace
} // namespace test
} // namespace tribblesat