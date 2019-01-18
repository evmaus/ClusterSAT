#ifndef SRC_SAT_CLAUSE_DATABASE_H
#define SRC_SAT_CLAUSE_DATABASE_H

#include "src/cnf/cnf_and_op.h"

namespace tribblesat {

class ClauseDatabase {
  public:
  ClauseDatabase(const cnf::And& term);
  
  void add_term(cnf::Or term);
  void compact();

  std::vector<cnf::Or> unit_terms(const VariableEnvironment& env) const;
  const cnf::And& learned_clauses() const { return learned_clauses_; }

  bool has_empty(const VariableEnvironment& env) const;
  cnf::Or next_empty(const VariableEnvironment& env) const;

  private:
  const cnf::And& term_;
  cnf::And learned_clauses_;

};
} // namespace tribblesat
#endif // SRC_SAT_CLAUSE_DATABASE_H