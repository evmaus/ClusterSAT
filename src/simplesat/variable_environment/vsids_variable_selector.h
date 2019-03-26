#ifndef SRC_CNF_VSIDS_VARIABLE_SELECTOR_H
#define SRC_CNF_VSIDS_VARIABLE_SELECTOR_H

#include <vector>
#include "src/simplesat/variable_environment/variable_environment.h"
#include "src/simplesat/variable_environment/variable_selector.h"
#include "src/simplesat/cnf/cnf_and_op.h"
#include "src/simplesat/common/stats.h"

namespace simplesat { 

using VariableStatePair = std::pair<variable_id, VariableState>;

// A variable selector is a ranking of variables to assign to.
// It's used by various variable environments to change how they choose the next unassigned variable.
class VSIDSVariableSelector : public VariableSelector {
  public:
  VSIDSVariableSelector(const cnf::And& term, double rescore, int period);
  VariableIterator cbegin() const override { return order_.cbegin(); }
  VariableIterator cend() const override { return order_.cend(); }
  VariableState recommend_assignment(variable_id id) const override;
  void recalculate(const cnf::Or& learned_term) override;

  private:
  void SortByScore();
  void DivideAllScores();
  double rescore_;
  int current_;
  int period_;
  std::map<int64_t, double> scores_;
  std::vector<variable_id> order_;
};

} // namespace simplesat
#endif // SRC_VARIABLE_SELECTION_VARIABLE_SELECTOR_H