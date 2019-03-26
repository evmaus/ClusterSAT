#include "src/simplesat/variable_environment/vsids_variable_selector.h"

namespace simplesat {

// Uses bubble sort, as the first sort is 'cheap' and later sorts
// will be mostly sorted.
void VSIDSVariableSelector::SortByScore() {
  bool sorted = false;
  while (!sorted) {
    sorted = true;
    for (int i = 0; i < order_.size()-1; i++) {
      uint64_t index1 = order_[i];
      uint64_t index2 = order_[i+1];
      
      double pos_score_i = scores_.at(index1);
      double pos_score_ip1 = scores_.at(index2);
      double score_i = std::max(pos_score_i, scores_.at(-(index1)));
      double score_ip1 = std::max(pos_score_ip1, scores_.at(-((index2))));
      if (score_ip1 > score_i) {
        int temp = order_[i+1];
        order_[i+1] = order_[i];
        order_[i] = temp;
        sorted = false;
      }
    }
  }
}

void VSIDSVariableSelector::DivideAllScores() {
  for(auto term : scores_) {
    scores_[term.first] = term.second * rescore_;
  }
}

VSIDSVariableSelector::VSIDSVariableSelector(const cnf::And& term, double rescore, int period) 
  : rescore_(rescore), period_(period)
{
  int max_id = term.variable_count();
  // Insert variable ids into linear order.
  order_.clear();
  order_.reserve(max_id);
  for (int i = 1; i <= max_id; i++) {
    order_.push_back(i);
  }
  
  // Score variables by occurrence.
  for (int i = -max_id; i <= max_id; i++) {
    scores_[i] = 0.0;
  }
  for (auto or_it = term.cbegin(); or_it != term.cend(); or_it++) {
    for (auto var = or_it->cbegin(); var != or_it->cend(); var++) {
      int64_t id = var->id();
      if (var->negated())
      {
        id = - id;
      }
      scores_[id] = scores_.at(id)+1;
    }
  }
  // Sort by score.
  SortByScore();
}

VariableState VSIDSVariableSelector::recommend_assignment(variable_id id) const {
  if (scores_.at(id) > scores_.at(-id))
    return VariableState::STRUE;
  else
    return VariableState::SFALSE;
}

void VSIDSVariableSelector::recalculate(const cnf::Or& learned_term) {
  for (auto var = learned_term.cbegin(); var != learned_term.cend(); var++) {
      scores_[var->id()] += 1;
  }
  current_++;
  if (period_ == current_) {
    DivideAllScores();
    current_ = 0;
  }
  SortByScore();
}
} // namespace simplesat