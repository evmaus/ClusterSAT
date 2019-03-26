#ifndef SRC_SAT_CLAUSE_DATABASE_H
#define SRC_SAT_CLAUSE_DATABASE_H

#include "src/simplesat/cnf/cnf_and_op.h"
#include "src/simplesat/variable_environment/environment_stack.h"
#include "src/simplesat/sat/compacting_policy.h"

namespace simplesat {

class ClauseDatabase {
  public:
  ClauseDatabase(cnf::And& term, 
                  std::unique_ptr<VariableEnvironmentStack>& env, 
                  std::unique_ptr<CompactingPolicy>& compacting_policy);
  
  void add_term(cnf::Or term);
  void compact(int decision_level);

  std::list<cnf::Or*> unit_terms();
  const cnf::And& learned_clauses() const { return learned_clauses_; }
  std::unique_ptr<VariableEnvironmentStack>& environment() { return env_stack_; }

  bool has_empty() const;
  cnf::Or next_empty() const;

  VariableRecommendation next_unbound();
  void assign(variable_id var, VariableState state);

  void push();
  void pop();
  void backtrack(int backtrack_level);

  private:
  cnf::And& term_;
  cnf::And learned_clauses_;
  std::unique_ptr<VariableEnvironmentStack>& env_stack_;
  const std::unique_ptr<CompactingPolicy>& compacting_policy_;
};
} // namespace simplesat
#endif // SRC_SAT_CLAUSE_DATABASE_H