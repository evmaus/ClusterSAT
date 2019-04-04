// Copyright 2019 Google LLC
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "src/clustersat/node/simplesat_wrapper.h"

#include <glog/logging.h>

namespace clustersat
{
simplesat::cnf::Or ClustersatOrToTribblesatOr(clustersat::OrTerm term) {
  std::vector<simplesat::cnf::Variable> variables;
  for (auto var : term.variables()) {
    int32_t var_index = var.id();
      if (var_index > 0){
        simplesat::cnf::Variable f(var_index);
        variables.push_back(f);
      } else {
        simplesat::cnf::Variable f(-var_index, true);
        variables.push_back(f);
      }
  }

  return simplesat::cnf::Or(variables);
}
simplesat::cnf::And ClustersatAndToTribblesatAnd(clustersat::AndTerm term) {
  std::list<simplesat::cnf::Or> or_terms;
  for (auto term : term.terms()) {
    or_terms.push_back(ClustersatOrToTribblesatOr(term));
  }
  
  return simplesat::cnf::And(or_terms);
}

clustersat::SatResult TribblesatResultToClustersatResult(simplesat::SatResult result) {
  clustersat::SatResult output;

  switch (result.first) {
    case simplesat::SatResultType::SAT:
      output.set_result(clustersat::SatResult::SAT);
      break;
    case simplesat::SatResultType::UNSAT:
      output.set_result(clustersat::SatResult::UNSAT);
      break;
    case simplesat::SatResultType::UNKNOWN:
      output.set_result(clustersat::SatResult::UNKNOWN);
      break;
  }
  auto assignments = result.second;
  for(auto assignment : assignments) {
    output.add_assignments()->set_id(assignment);
  }

  return output;
}

SimpleSatWrapper::SimpleSatWrapper(simplesat::SatStrategy& strategy) : strategy_(strategy)
{

}

clustersat::SatResult SimpleSatWrapper::GetSatisfiability(clustersat::AndTerm term, std::atomic_bool& should_run) {
  auto andTerm = ClustersatAndToTribblesatAnd(term);
  LOG(INFO) << "Starting SAT";
  simplesat::SatResult result = strategy_.DetermineCnfSatWithCancellation(andTerm, should_run);
  LOG(INFO) << "Finished SAT";
  return TribblesatResultToClustersatResult(std::move(result));
}


} // clustersat