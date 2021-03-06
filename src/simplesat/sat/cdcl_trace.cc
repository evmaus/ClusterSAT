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

#include "src/simplesat/sat/cdcl_trace.h"
#include "src/simplesat/sat/clause_database.h"
#include <string>
#include <sstream>
#include <glog/logging.h>

namespace simplesat {

CDCLTraceTerm::CDCLTraceTerm(int dl, cnf::Variable v, VariableState s)
  : decision_level(dl), variable(v), state(s), unit(false)
{
  std::vector<cnf::Variable> vars;
  if (s == VariableState::SFALSE) {
    vars.push_back(v.negate());
  } else {
    vars.push_back(v);
  }
  term = cnf::Or(vars);
}

CDCLTraceTerm::CDCLTraceTerm(int decision_level, cnf::Variable variable, VariableState state, cnf::Or term)
  : decision_level(decision_level), variable(variable), state(state), unit(true), term(term)
{

}

std::string printable_node(CDCLTraceTerm term) {
  std::string s = term.variable.to_string() + "@" +
    std::to_string(term.decision_level) + " -> " 
    + VariableEnvironment::StateToString(term.state)
    + " ( " + term.term.to_string() + " )";
  return s;
}

std::string CDCLTrace::to_string() {
  std::ostringstream stream;
  for (auto terms_it = trace_.cbegin(); terms_it != trace_.cend(); terms_it++ ) {
    stream << printable_node(*terms_it) << std::endl;
  }

  return stream.str();
}

void CDCLTrace::AddAssignmentChoice(int decision_level, cnf::Variable variable, VariableState state) {
  CDCLTraceTerm trace_term(decision_level, variable, state);
  last_decision_level_[variable.id()] = decision_level;
  trace_.push_back(trace_term);
}

void CDCLTrace::AddUnitPropagation(int decision_level, cnf::Variable variable, VariableState state, cnf::Or term) {
  CDCLTraceTerm trace_term(decision_level, variable, state, term);
  last_decision_level_[variable.id()] = decision_level;
  trace_.push_back(trace_term);
}

int CDCLTrace::litsAtLevel(cnf::Or conflict_term, int decision_level) {
  int lit_at_level = 0;

  for (auto var_it = conflict_term.cbegin(); var_it != conflict_term.cend(); var_it++) {
    if(last_decision_level_[var_it->id()]== decision_level) {
      lit_at_level++;
    }
  }
  return lit_at_level;
}

// Potential TODO:  Use the map instead of iterating from the back.
// Unclear which will be
CDCLTraceTerm CDCLTrace::getLastAssignedInTerm(const cnf::Or& conflict_term) {
  for (auto terms_it = trace_.cend(); terms_it-- != trace_.cbegin(); ) {
    for (auto var_it = conflict_term.cbegin(); var_it != conflict_term.cend(); var_it++) {     
      if(var_it->id() == terms_it->variable.id()) {
          return *terms_it;
      }
    }
  }
  return CDCLTraceTerm(-1, cnf::Variable(1), VariableState::SUNBOUND);
}

cnf::Or Resolve(CDCLTraceTerm term, cnf::Or conflict_term) {
  return conflict_term.combine_with(term.term);
}

int CDCLTrace::getSecondToLastLevelOfTerm(int decision_level, cnf::Or term) {
  int current_max = 0;
  int second_max = 0;
  if (term.count() == 1)
    return 0;

  for (auto var_it = term.cbegin(); var_it != term.cend(); var_it++) { 
    int var_level = last_decision_level_[var_it->id()];
    if (var_level > current_max && var_level <= decision_level) {
      second_max = current_max;
      current_max = var_level;
    } else if (var_level > second_max) {
      second_max = var_level;
    }
  }
  return second_max;
}

std::pair<int, cnf::Or> CDCLTrace::LearnClauses(int decision_level, const ClauseDatabase& clause_db, const VariableEnvironment& env) {
  // Conflict at DL 0, no work to do.
  if (decision_level == 0) {
    return std::pair<int, cnf::Or>(-1, cnf::Or());  
  }
  
  LOG(INFO) << ( "Trace: " + to_string());
  cnf::Or conflict_term = clause_db.next_empty();
  int curr_lit_count = litsAtLevel(conflict_term, decision_level);
  while (curr_lit_count != 1) {
    LOG(INFO) << ( "Current lit count " + std::to_string(curr_lit_count));
    CDCLTraceTerm next_term = getLastAssignedInTerm(conflict_term);
    LOG(INFO) << ( "Merging: " + conflict_term.to_string() + " with " + next_term.term.to_string());
    conflict_term = Resolve(next_term, conflict_term);
    curr_lit_count = litsAtLevel(conflict_term, decision_level);
  }

  return std::pair<int, cnf::Or>(
    getSecondToLastLevelOfTerm(decision_level, conflict_term),
    conflict_term
  );
}

void CDCLTrace::Backtrack(int backtrack_level) {
  if (backtrack_level == 0)
  {
    trace_.clear();
    LOG(INFO) << ( "Backtrack to zero left " + std::to_string(trace_.size()) + " elements");
    return;
  }

  int current_level = trace_.at(trace_.size()-1).decision_level;
  while (current_level > backtrack_level) {
    trace_.pop_back();
    current_level = trace_.at(trace_.size()-1).decision_level;
  }
}

} // namespace simplesat