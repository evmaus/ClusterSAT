#include "src/cnf/cnf_or_op.h"

#include <vector>
#include <sstream>

#include "src/cnf/cnf_variable.h"
#include "src/common/log.h"

namespace tribblesat {
namespace cnf {
Or::Or(std::vector<Variable> variables) : variables_(variables) { }

TermState Or::term_state(const VariableEnvironment& env) const
{
  int count_unbound = 0;
  
  for (auto var : variables_) {
    switch(var.GetValueInEnvironment(env)) {
      case VariableState::STRUE:
        // SAT if any is true
        return TermState::SAT;
      case VariableState::SFALSE:
        break;
      case VariableState::SUNBOUND:
        count_unbound++;
    }
  }

  if (count_unbound == 0) {
    // UNSAT if all are false.
    return TermState::UNSAT;
  } else if (count_unbound == 1) {
    // UNIT if all are false but one.
    return TermState::UNIT;
  } else {
    // UNRESOLVED otherwise.
    return TermState::UNRESOLVED;
  }
}

variable_id Or::max_variable() const {
  variable_id max = 0;
  for (auto var : variables_) {
    if (var.id() > max) {
      max = var.id();
    }
  }
  return max;
}

std::string Or::to_string() const {
  std::ostringstream stream;
  for (auto term : variables_) {
    stream << " v " << term.to_string();
  }
  return stream.str();
}

Variable Or::first_unassigned(const VariableEnvironment& env) const {
  for (auto var : variables_) {
    switch(var.GetValueInEnvironment(env)) {
      case VariableState::STRUE:
      case VariableState::SFALSE:
        break;
      case VariableState::SUNBOUND:
        return var;
    }
  }

  return 0;
}

Or Or::combine_with(Or other_term){
  std::vector<Variable> vars = variables_;
  
  for (auto it = other_term.cbegin(); it != other_term.cend(); it++) {
    bool present = false;
    int idx = -1;
    for(int i=0; i < vars.size(); i++) {
      if (it->id() == vars[i].id()) {
        present = true;
        idx = i;
      }
    }
    if (!present) {
      vars.push_back(*it);
    } else {
      if (it->negated() != vars[idx].negated()) {
        vars.erase(vars.begin() + idx);
      }
    }
  }
  return cnf::Or(vars);
}

} // namespace cnf
} // namespace tribblesat