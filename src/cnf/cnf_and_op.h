#ifndef SRC_CNF_CNF_AND_OP_H
#define SRC_CNF_CNF_AND_OP_H

#include "src/cnf/cnf_or_op.h"
#include <vector>

namespace tribblesat {
namespace cnf {
class And {
  public:
  And(std::vector<Or> terms);
  std::string to_string() const;

  void add_term(Or term);
  bool satisfied(const VariableEnvironment& env) const;
  variable_id variable_count() const;
  bool has_unit(const VariableEnvironment& env) const;
  Or next_unit(const VariableEnvironment& env) const;
  bool has_empty(const VariableEnvironment& env) const;
  Or next_empty(const VariableEnvironment& env) const;
  std::vector<Or> unit_terms(const VariableEnvironment& env) const;
  std::vector<Or> empty_terms(const VariableEnvironment& env) const;

  std::vector<Or>::const_iterator cbegin() const { return terms_.cbegin(); }
  std::vector<Or>::const_iterator cend() const { return terms_.cend(); }

  private:
  std::vector<Or> terms_;

};
} // namespace cnf
} // namespace tribblesat
#endif