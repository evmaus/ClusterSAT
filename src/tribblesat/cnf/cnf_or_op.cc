#include "src/tribblesat/cnf/cnf_or_op.h"

#include <vector>
#include <sstream>

#include "src/tribblesat/cnf/cnf_variable.h"

namespace tribblesat {
namespace cnf {
Or::Or(std::vector<Variable> variables) : variables_(variables) 
{
  first_watched_literal_ = 0;
  second_watched_literal_ = variables_.size()-1;
}

bool Assigned(const VariableState state){
  switch(state) {
    case VariableState::STRUE:
      case VariableState::SFALSE:
        return true;
      case VariableState::SUNBOUND:
        return false;
  }
}

bool True(const VariableState state) {
  switch(state) {
    case VariableState::STRUE:
        return true;
    case VariableState::SFALSE:
    case VariableState::SUNBOUND:
      return false;
  }
}

bool False(const VariableState state) {
  switch(state) {
    case VariableState::STRUE:
        return true;
    case VariableState::SFALSE:
    case VariableState::SUNBOUND:
      return false;
  }
}

TermState Or::term_state(const VariableEnvironment& env)
{
  int count_unbound = 0;
  
  for (auto var : variables_) {
    if(True(var.GetValueInEnvironment(env))) {
      return TermState::SAT;
    }
    else if (!Assigned(var.GetValueInEnvironment(env))) {
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

Variable Or::first_unassigned(const VariableEnvironment& env) {
  if (!Assigned(variables_[first_watched_literal_].GetValueInEnvironment(env))) {
    return variables_[first_watched_literal_];
  }
  for (int i = 0; i < variables_.size(); i++) {
    if(!Assigned(variables_[i].GetValueInEnvironment(env))) {
      first_watched_literal_ = i;
      return variables_[i];
    }
  }
  first_watched_literal_ = 0;
  return Variable(0);
}

Variable Or::last_unassigned(const VariableEnvironment& env) {
  if (!Assigned(variables_[second_watched_literal_].GetValueInEnvironment(env))) {
    return variables_[second_watched_literal_];
  }
  for (int i = variables_.size()-1; i >= 0; i--) {
    if(!Assigned(variables_[i].GetValueInEnvironment(env))) {
      second_watched_literal_ = i;
      return variables_[i];
    }
  }
  second_watched_literal_ = 0;
  return Variable(0);
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