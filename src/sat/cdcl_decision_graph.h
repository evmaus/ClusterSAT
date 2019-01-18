#ifndef SRC_SAT_CDCL_DECISION_GRAPH_H
#define SRC_SAT_CDCL_DECISION_GRAPH_H

#include "src/cnf/cnf_variable_environment.h"

#include <string>
#include <vector>
#include <map>

#include "src/cnf/cnf_or_op.h"

namespace tribblesat {

using NodeKey = std::pair<cnf::variable_id, cnf::VariableState>;

struct DecisionGraphNode {
  bool conflict_node;
  int decision_level;
  cnf::variable_id variable_id;
  cnf::VariableState variable_state;
};

class DecisionGraph {
  public:
  DecisionGraph();
  void AddArbitraryDecision(int decision_level, cnf::variable_id variable_id, cnf::VariableState state);
  void AddUnitDecision(int decision_level, cnf::variable_id variable_id, cnf::VariableState state, cnf::Or term);
  
  void Backtrack(int decision_level);
  
  std::vector<NodeKey> GetParents(NodeKey key);
  DecisionGraphNode GetNode(NodeKey key);

  std::string to_string();
  
  NodeKey conflict_node() { return conflict_node_id_; };

  std::map<NodeKey, DecisionGraphNode>::const_iterator nodes_cbegin() const { return nodes_.cbegin(); }
  std::map<NodeKey, DecisionGraphNode>::const_iterator nodes_cend() const { return nodes_.cend(); }
  int nodes_count() const { return nodes_.size(); }

  std::vector<std::tuple<NodeKey, NodeKey, int>>::const_iterator edges_cbegin() const { return edges_.cbegin(); }
  std::vector<std::tuple<NodeKey, NodeKey, int>>::const_iterator edges_cend() const { return edges_.cend(); }
  int edges_count() const { return edges_.size(); }

  static std::string node_name(NodeKey key);
  static std::string printable_node(DecisionGraphNode node);

  private:
  NodeKey conflict_node_id_;
  std::map<NodeKey, DecisionGraphNode> nodes_;
  std::vector<std::tuple<NodeKey, NodeKey, int>> edges_;
};

} // namespace tribblesat

#endif // SRC_SAT_CDCL_DECISION_GRAPH_H