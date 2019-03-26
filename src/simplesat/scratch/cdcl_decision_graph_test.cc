#include "src/sat/cdcl_decision_graph.h"

#include "googletest/include/gtest/gtest.h"
#include "src/common/log.h"

namespace tribblesat {
namespace test {
namespace {

TEST(CDCLDecisionGraphTest, EmptyGraphTest) {
  DecisionGraph graph;
  EXPECT_EQ(graph.nodes_count(), 1);
  EXPECT_EQ(graph.edges_count(), 0);
}

TEST(CDCLDecisionGraphTest, AddArbitraryNodeTest) {
  DecisionGraph graph;
  graph.AddArbitraryDecision(1, 1, cnf::VariableState::STRUE);
  EXPECT_EQ(graph.nodes_count(), 2);
  EXPECT_EQ(graph.edges_count(), 0);
}

TEST(CDCLDecisionGraphTest, AddUnitNodeTest) {
  DecisionGraph graph;
  std::vector<cnf::Variable> vars;
  vars.push_back(cnf::Variable(1));
  vars.push_back(cnf::Variable(2));
  cnf::Or term(vars);
  graph.AddArbitraryDecision(1, 1, cnf::VariableState::SFALSE);

  graph.AddUnitDecision(1, 2, cnf::VariableState::STRUE, term);
  LOG(LogLevel::VERBOSE, graph.to_string());
  EXPECT_EQ(graph.nodes_count(), 3);
  EXPECT_EQ(graph.edges_count(), 1);
}


TEST(CDCLDecisionGraphTest, ConflictNodeTest) {
  DecisionGraph graph;
  std::vector<cnf::Variable> vars1;
  vars1.push_back(cnf::Variable(1));
  vars1.push_back(cnf::Variable(2));
  cnf::Or term1(vars1);

  std::vector<cnf::Variable> vars2;
  vars2.push_back(cnf::Variable(1));
  vars2.push_back(cnf::Variable(2, true));
  cnf::Or term2(vars2);
  
  graph.AddArbitraryDecision(1, 1, cnf::VariableState::SFALSE);
  graph.AddUnitDecision(1, 2, cnf::VariableState::STRUE, term1);
  graph.AddUnitDecision(1, 2, cnf::VariableState::SFALSE, term2);

  LOG(LogLevel::VERBOSE, graph.to_string());
  EXPECT_EQ(graph.nodes_count(), 4);
  EXPECT_EQ(graph.edges_count(), 4);
}

TEST(CDCLDecisionGraphTest, BacktrackTest) {
  SET_LOG_LEVEL(LogLevel::VERBOSE);
  DecisionGraph graph;
  std::vector<cnf::Variable> vars1;
  vars1.push_back(cnf::Variable(1));
  vars1.push_back(cnf::Variable(2));
  cnf::Or term1(vars1);

  std::vector<cnf::Variable> vars2;
  vars2.push_back(cnf::Variable(1));
  vars2.push_back(cnf::Variable(2, true));
  cnf::Or term2(vars2);
  
  graph.AddArbitraryDecision(1, 1, cnf::VariableState::SFALSE);
  graph.AddUnitDecision(2, 2, cnf::VariableState::STRUE, term1);
  graph.AddUnitDecision(2, 2, cnf::VariableState::SFALSE, term2);
  graph.Backtrack(1);

  LOG(LogLevel::VERBOSE, graph.to_string());
  EXPECT_EQ(graph.nodes_count(), 2);
  EXPECT_EQ(graph.edges_count(), 0);
}

} // namespace
} // namespace test
} // namespace tribblesat