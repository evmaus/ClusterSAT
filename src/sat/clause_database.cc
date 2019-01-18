
#include "src/sat/clause_database.h"

namespace tribblesat {
ClauseDatabase::ClauseDatabase(const cnf::And& term) 
  : term_(term) 
{ }

void ClauseDatabase::add_term(cnf::Or term) {
  learned_clauses_.add_term(term);
}

void ClauseDatabase::compact() {
  // TODO
}

std::vector<cnf::Or> ClauseDatabase::unit_terms(const VariableEnvironment& env) const {
  std::vector<cnf::Or> units = term_.unit_terms(env);
  std::vector<cnf::Or> learned_units = learned_clauses_.unit_terms(env);
  for (auto unit : learned_units) {
    units.push_back(unit);
  }
  return units;
}

bool ClauseDatabase::has_empty(const VariableEnvironment& env) const {
  return term_.has_empty(env) || learned_clauses_.has_empty(env);
}

cnf::Or ClauseDatabase::next_empty(const VariableEnvironment& env) const {
  if (term_.has_empty(env)) {
    return term_.next_empty(env);
  } else {
    return learned_clauses_.next_empty(env);
  }
}

} // namespace tribblesat