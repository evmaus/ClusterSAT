#ifndef SRC_CNF_CNF_VARIABLE_H
#define SRC_CNF_CNF_VARIABLE_H

#include "src/variable_environment/variable_environment.h"

namespace tribblesat {
namespace cnf {

class Variable {
  public:
  Variable(variable_id variable);
  Variable(variable_id variable, bool negated);
  VariableState GetValueInEnvironment(const VariableEnvironment& env) const;

  variable_id id() const { return variable_; }
  bool negated() const { return negated_; }

  Variable negate() const { return Variable(variable_, !negated_); }
  std::string to_string() const;

  private:
  variable_id variable_;
  bool negated_;
};
} // namespace cnf
} // namespace tribblesat

#endif