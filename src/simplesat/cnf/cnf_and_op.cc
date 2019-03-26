#include "src/simplesat/cnf/cnf_and_op.h"
#include "src/simplesat/cnf/cnf_or_op.h"
#include <sstream>
#include <iostream>
#include <glog/logging.h>

namespace simplesat {
namespace cnf {
And::And(std::list<Or> terms) : terms_(terms) { };

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


std::list<Or*> And::unit_terms(const VariableEnvironment& env) {
  std::list<Or*> unit_terms;
  for (auto it = terms_.begin(); it != terms_.end(); it++) {
    if (it->term_state(env) == TermState::UNIT) {
      unit_terms.push_back(&*it);
    }
  }
  return unit_terms;
}

std::list<Or*> And::empty_terms(const VariableEnvironment& env) {
  std::list<Or*> empty_terms;
  for (auto it = terms_.begin(); it != terms_.end(); it++) {
    if (it->term_state(env) == TermState::UNSAT) {
      empty_terms.push_back(&*it);
    }
  }
  return empty_terms;
}

Or And::next_empty(const VariableEnvironment& env) const {
  for (auto term : terms_) {
    if (term.term_state(env) == TermState::UNSAT) {
      return term;
    }
  }
  LOG(ERROR) << "Called next_empty and none was found.";
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
} // namespace simplesat