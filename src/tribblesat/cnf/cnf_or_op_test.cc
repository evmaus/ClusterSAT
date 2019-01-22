#include "src/tribblesat/cnf/cnf_or_op.h"

#include <vector>

#include "src/tribblesat/variable_environment/vector_environment.h"
#include "src/tribblesat/variable_environment/linear_variable_selector.h"
#include "googletest/include/gtest/gtest.h"

namespace tribblesat {
namespace cnf {
namespace {

TEST(CnfOrOp, GetTermState_TermIsSat) {
  Variable v0(0);
  Variable v1(1);
  VectorVariableEnvironment env(2, LinearVariableSelector(2));
  env.assign(0, VariableState::STRUE);
  env.assign(1, VariableState::SUNBOUND);
  std::vector<Variable> vars;
  vars.push_back(v0);
  vars.push_back(v1);
  Or or_term(vars);
  EXPECT_EQ(or_term.term_state(env), TermState::SAT);
}

TEST(CnfOrOp, GetTermState_TermIsUnsat) {

  Variable v0(0);
  Variable v1(1);
  VectorVariableEnvironment env(2, LinearVariableSelector(2));
  env.assign(0, VariableState::SFALSE);
  env.assign(1, VariableState::SFALSE);
  std::vector<Variable> vars;
  vars.push_back(v0);
  vars.push_back(v1);
  Or or_term(vars);
  EXPECT_EQ(or_term.term_state(env), TermState::UNSAT);
}

TEST(CnfOrOp, GetTermState_TermIsUnit) {
  Variable v0(0);
  Variable v1(1);
  VectorVariableEnvironment env(2, LinearVariableSelector(2));
  env.assign(0, VariableState::SFALSE);
  env.assign(1, VariableState::SUNBOUND);
  std::vector<Variable> vars;
  vars.push_back(v0);
  vars.push_back(v1);
  Or or_term(vars);
  EXPECT_EQ(or_term.term_state(env), TermState::UNIT);
}

TEST(CnfOrOp, GetTermState_TermIsUnresolved) {
  Variable v0(0);
  Variable v1(1);
  VectorVariableEnvironment env(2, LinearVariableSelector(2));
  env.assign(0, VariableState::SUNBOUND);
  env.assign(1, VariableState::SUNBOUND);
  std::vector<Variable> vars;
  vars.push_back(v0);
  vars.push_back(v1);
  Or or_term(vars);
  EXPECT_EQ(or_term.term_state(env), TermState::UNRESOLVED);
}

TEST(CnfOrOp, FirstUnassigned_AllAssigned){
  Variable v0(0);
  Variable v1(1);
  VectorVariableEnvironment env(2, LinearVariableSelector(2));
  env.assign(0, VariableState::STRUE);
  env.assign(1, VariableState::SFALSE);
  std::vector<Variable> vars;
  vars.push_back(v0);
  vars.push_back(v1);
  Or or_term(vars);
  EXPECT_EQ(or_term.first_unassigned(env).id(), 0);
}

TEST(CnfOrOp, FirstUnassigned){
  Variable v0(0);
  Variable v1(5);
  VectorVariableEnvironment env(5, LinearVariableSelector(2));
  env.assign(0, VariableState::STRUE);
  env.assign(5, VariableState::SUNBOUND);
  std::vector<Variable> vars;
  vars.push_back(v0);
  vars.push_back(v1);
  Or or_term(vars);
  EXPECT_EQ(or_term.first_unassigned(env).id(), 5);
}

} // namespace
} // namespace test
} // namespace tribblesat