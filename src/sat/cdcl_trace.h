#ifndef SRC_SAT_CDCL_TRACE_H
#define SRC_SAT_CDCL_TRACE_H

#include <vector>
#include <map>

#include "src/cnf/cnf_variable.h"
#include "src/cnf/cnf_or_op.h"
#include "src/cnf/cnf_and_op.h"
#include "src/sat/clause_database.h"

namespace tribblesat {

struct CDCLTraceTerm {
  CDCLTraceTerm(int decision_level, cnf::Variable variable, VariableState state);
  CDCLTraceTerm(int decision_level, cnf::Variable variable, VariableState state, cnf::Or term);

  int decision_level;
  cnf::Variable variable;
  VariableState state;
  bool unit;
  cnf::Or term;
};

class CDCLTrace {
  public:
  void AddAssignmentChoice(int decision_level, cnf::Variable v, VariableState state);
  void AddUnitPropagation(int decision_level, cnf::Variable v, VariableState state, cnf::Or term);
  std::pair<int, cnf::Or> LearnClauses(int decision_level, const ClauseDatabase& term, const VariableEnvironment& env);
  void Backtrack(int backtrack_level);
  std::string to_string();
  private:
  int litsAtLevel(cnf::Or conflict_term, int decision_level);
  CDCLTraceTerm getLastAssignedInTerm(const cnf::Or& conflict_term);
  int getSecondToLastLevelOfTerm(int decision_level, cnf::Or term);

  std::vector<CDCLTraceTerm> trace_;
  std::map<variable_id, int> last_decision_level_;
};


} // namespace tribblesat


#endif // SRC_SAT_CDCL_TRACE_H