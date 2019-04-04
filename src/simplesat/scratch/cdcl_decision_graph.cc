// Copyright 2019 Google LLC
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "src/sat/cdcl_decision_graph.h"

#include <string>
#include <sstream>

#include "src/cnf/cnf_variable_environment.h"
#include "src/common/log.h"
namespace tribblesat {

DecisionGraph::DecisionGraph() {
  DecisionGraphNode node;
  node.conflict_node = true;
  node.decision_level = -1;
  node.variable_id = 0;
  node.variable_state = cnf::VariableState::SUNBOUND;
  conflict_node_id_ = NodeKey(0, cnf::VariableState::SUNBOUND);
  nodes_[conflict_node_id_] = node;
}

void DecisionGraph::AddArbitraryDecision(int decision_level, 
  cnf::variable_id variable_id,
  cnf::VariableState state)
{
  DecisionGraphNode node;
  node.conflict_node = false;
  node.decision_level = decision_level;
  node.variable_id = variable_id;
  node.variable_state = state;
  nodes_[NodeKey(variable_id, state)] = node;
}

void DecisionGraph::AddUnitDecision(int decision_level, 
  cnf::variable_id variable_id, 
  cnf::VariableState state, 
  cnf::Or term)
{
  NodeKey key = NodeKey(variable_id, state); 
  DecisionGraphNode node;
  node.conflict_node = false;
  node.decision_level = decision_level;
  node.variable_id = variable_id;
  node.variable_state = state;

  for (auto it = term.cbegin(); it != term.cend(); it++){
    if(it->id() != variable_id) {
      NodeKey parent = NodeKey(it->id(), 
            it->negated() ? cnf::VariableState::STRUE : cnf::VariableState::SFALSE
          );
      edges_.push_back(
        std::tuple<NodeKey, NodeKey, int>(
          parent,
          key,
          decision_level
        ));
    }
  }
  auto find = nodes_.find(key);
  if (find == nodes_.end()) {
    nodes_[key] = node;
  }

  NodeKey opposite = NodeKey(variable_id, cnf::VariableEnvironment::Not(state)); 
  auto search = nodes_.find(opposite);
  if (search != nodes_.end()) {
    edges_.push_back(
      std::tuple<NodeKey, NodeKey, int>(
      opposite,
      conflict_node_id_,
      decision_level)
    );
    edges_.push_back(
      std::tuple<NodeKey, NodeKey, int>(
      key,
      conflict_node_id_,
      decision_level)
    );
  }
}

std::vector<NodeKey> DecisionGraph::GetParents(NodeKey key) {
  std::vector<NodeKey> parents;
  for (auto edge : edges_) {
    if (std::get<1>(edge) == key) {
      parents.push_back(std::get<0>(edge));
    }
  }
  return parents;
}

DecisionGraphNode DecisionGraph::GetNode(NodeKey key) {
  return nodes_[key];
}


void DecisionGraph::Backtrack(int decision_level) {
  // Remove all nodes with decision level > decision_level.
  for (auto node : nodes_) {
    if (node.second.decision_level > decision_level) {
      nodes_.erase(node.first);
    }
  }
  // Remove all edges with decision level > decision_level.
  for (auto it = edges_.end(); it-- != edges_.begin(); ) {
    if (std::get<2>(*it) > decision_level) {
      edges_.erase(it);
    }
  }
}

std::string DecisionGraph::node_name(NodeKey key) {
  return "n" + std::to_string(key.first) + "_" + std::to_string(key.second);
}

std::string DecisionGraph::printable_node(DecisionGraphNode node) {
  return node_name(NodeKey(node.variable_id, node.variable_state)) + " [label=\"" 
  + std::to_string(node.variable_id) + "@" + std::to_string(node.decision_level) + "," +
  cnf::VariableEnvironment::StateToString(node.variable_state) + 
  "\"]";
}


std::string DecisionGraph::to_string() {
  std::ostringstream stream;
  stream << "digraph ImplicationGraph {" << std::endl;
  for (auto node : nodes_) {
    stream << " " << printable_node(node.second) << std::endl;
  }
  for (auto edge : edges_) {
    stream  << node_name(std::get<0>(edge)) 
            << " -> " << node_name(std::get<1>(edge))
            << "[label=\"@" << std::get<2>(edge) << "\"]" << std::endl;
  }
  stream << "}" << std::endl;
  return stream.str();
}

} // namespace tribblesat
