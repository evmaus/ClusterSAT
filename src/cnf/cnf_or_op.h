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
  TermState term_state(const VariableEnvironment& env) const;
  variable_id max_variable() const;
  Variable first_unassigned(const VariableEnvironment& env) const;
  std::string to_string() const;

  // Combine terms and remove units.
  cnf::Or combine_with(cnf::Or other_term);


  std::vector<Variable>::const_iterator cbegin() const { return variables_.cbegin(); }
  std::vector<Variable>::const_iterator cend() const { return variables_.cend(); }
  int count() const { return variables_.size(); }

  private:
  std::vector<Variable> variables_;
};
} // namespace cnf
} // namespace tribblesat


#endif