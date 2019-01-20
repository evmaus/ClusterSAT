#ifndef SRC_CNF_CNF_OR_OP_H
#define SRC_CNF_CNF_OR_OP_H

#include "src/cnf/cnf_variable.h"
#include <vector>

namespace tribblesat {
namespace cnf {

enum TermState {
  SAT,
  UNSAT,
  UNIT,
  UNRESOLVED
};

class Or {
  public:
  Or() {}
  Or(std::vector<Variable> variables);
  TermState term_state(const VariableEnvironment& env);
  variable_id max_variable() const;
  Variable first_unassigned(const VariableEnvironment& env);
  Variable last_unassigned(const VariableEnvironment& env);
  std::string to_string() const;

  // Combine terms and remove units.
  cnf::Or combine_with(cnf::Or other_term);


  std::vector<Variable>::const_iterator cbegin() const { return variables_.cbegin(); }
  std::vector<Variable>::const_iterator cend() const { return variables_.cend(); }
  std::vector<Variable>::iterator begin() { return variables_.begin(); }
  std::vector<Variable>::iterator end() { return variables_.end(); }
  int count() const { return variables_.size(); }

  private:
  std::vector<Variable> variables_;
  int first_watched_literal_;
  int second_watched_literal_;
};
} // namespace cnf
} // namespace tribblesat


#endif