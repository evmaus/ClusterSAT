#include "src/cnf/cnf_and_op.h"
#include "src/cnf/cnf_or_op.h"
#include <sstream>
#include <iostream>
#include "src/common/log.h"

namespace tribblesat {
namespace cnf {
And::And(std::vector<Or> terms) : terms_(terms) { };

bool And::satisfied(const VariableEnvironment& env) const {
  for (auto term : terms_) {
    if (term.term_state(env) != TermState::SAT) {
      return false;
    }
  }
  return true;
}

void And::add_term(Or term) {
  terms_.push_back(term);
}

bool And::has_unit(const VariableEnvironment& env) const {
  for (auto term : terms_) {
    if (term.term_state(env) == TermState::UNIT) {
      return true;
    }
  }
  return false;
}

bool And::has_empty(const VariableEnvironment& env) const {
  for (auto term : terms_) {
    if (term.term_state(env) == TermState::UNSAT) {
      return true;
    }
  }
  return false;
}


std::vector<Or> And::unit_terms(const VariableEnvironment& env) const {
  std::vector<Or> unit_terms;
  for (auto term : terms_) {
    if (term.term_state(env) == TermState::UNIT) {
      unit_terms.push_back(term);
    }
  }
  return unit_terms;
}

std::vector<Or> And::empty_terms(const VariableEnvironment& env) const {
  std::vector<Or> empty_terms;
  for (auto term : terms_) {
    if (term.term_state(env) == TermState::UNSAT) {
      empty_terms.push_back(term);
    }
  }
  return empty_terms;
}

Or And::next_unit(const VariableEnvironment& env) const {
  for (auto term : terms_) {
    if (term.term_state(env) == TermState::UNIT) {
      return term;
    }
  }
  LOG(LogLevel::ERROR, "Called next_unit and none was found.");
  std::vector<Variable> vec;
  return Or(vec);
}

Or And::next_empty(const VariableEnvironment& env) const {
  for (auto term : terms_) {
    if (term.term_state(env) == TermState::UNSAT) {
      return term;
    }
  }
  LOG(LogLevel::ERROR, "Called next_empty and none was found.");
  std::vector<Variable> vec;
  return Or(vec);
}


variable_id And::variable_count() const {
  variable_id max = 0;
  for (auto term : terms_) {
    if (term.max_variable() > max) {
      max = term.max_variable();
    }
  }
  return max;
}

std::string And::to_string() const {
  std::ostringstream stream;
  for (auto term : terms_) {
    stream << " ^ ( " << term.to_string() << " )";
  }
  return stream.str();
}

} // namespace cnf
} // namespace tribblesat