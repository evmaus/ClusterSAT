#include "src/clustersat/node/tribblesat_wrapper.h"


namespace clustersat
{
tribblesat::cnf::Or ClustersatOrToTribblesatOr(clustersat::OrTerm term) {
  std::vector<tribblesat::cnf::Variable> variables;
  for (auto var : term.variables()) {
    int32_t var_index = var.id();
      if (var_index > 0){
        tribblesat::cnf::Variable f(var_index);
        variables.push_back(f);
      } else {
        tribblesat::cnf::Variable f(-var_index, true);
        variables.push_back(f);
      }
  }

  return tribblesat::cnf::Or(variables);
}
tribblesat::cnf::And ClustersatAndToTribblesatAnd(clustersat::AndTerm term) {
  std::list<tribblesat::cnf::Or> or_terms;
  for (auto term : term.terms()) {
    or_terms.push_back(ClustersatOrToTribblesatOr(term));
  }
  
  return tribblesat::cnf::And(or_terms);
}

clustersat::SatResult TribblesatResultToClustersatResult(tribblesat::SatResult result) {
  clustersat::SatResult output;

  switch (result.first) {
    case tribblesat::SatResultType::SAT:
      output.set_result(clustersat::SatResult::SAT);
      break;
    case tribblesat::SatResultType::UNSAT:
      output.set_result(clustersat::SatResult::UNSAT);
      break;
    case tribblesat::SatResultType::UNKNOWN:
      output.set_result(clustersat::SatResult::UNKNOWN);
      break;
  }
  auto assignments = result.second;
  for(auto assignment : assignments) {
    output.add_assignments()->set_id(assignment);
  }

  return output;
}

TribbleSatWrapper::TribbleSatWrapper(tribblesat::SatStrategy& strategy) : strategy_(strategy)
{

}

clustersat::SatResult TribbleSatWrapper::GetSatisfiability(clustersat::AndTerm term) {
  auto andTerm = ClustersatAndToTribblesatAnd(term);
  tribblesat::SatResult result = strategy_.DetermineCnfSat(andTerm);
  return TribblesatResultToClustersatResult(std::move(result));
}


} // clustersat