#include "src/sat/compacting_policy.h"

namespace tribblesat {

/// Term Size compacting policy.
TermSizeCompactingPolicy::TermSizeCompactingPolicy(
    int compact_below_level, 
    int term_size, 
    int keep_terms)
  : compact_below_level_(compact_below_level), term_size_(term_size), keep_terms_(keep_terms)
{

}

bool TermSizeCompactingPolicy::should_compact(int decision_level) const {
  return decision_level <= compact_below_level_;
}

bool TermSizeCompactingPolicy::remove_term(int term_number, const cnf::Or& term) const {
  return term.count() > term_size_;
}
/// End Term Size compacting policy.

} // namespace tribblesat