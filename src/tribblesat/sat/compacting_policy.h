#ifndef SRC_SAT_COMPACTING_POLICY_H
#define SRC_SAT_COMPACTING_POLICY_H

#include "src/tribblesat/cnf/cnf_or_op.h"

namespace tribblesat {

enum class CompactingPolicyType {
  NONE,
  TERM_SIZE,
};

class CompactingPolicy {
  public:
  virtual ~CompactingPolicy() {};
  // Determine if it's time to compact.
  virtual bool should_compact(int decision_level) const = 0;

  // Determine if a term should be removed from the stack.
  virtual bool remove_term(int term_number, const cnf::Or& term) const = 0;

  // How many recent terms do we want to keep?
  virtual int keep_last() const = 0;
};


// Remove a term if it's larger than a certain size.
class KeepAllCompactingPolicy : public CompactingPolicy {
  public:
  KeepAllCompactingPolicy() {}
  
  bool should_compact(int decision_level) const override { return false; };
  bool remove_term(int term_number, const cnf::Or& term) const override { return false; };
  virtual int keep_last() const override { return 1000000; } // Should probably be int_max.
};


// Remove a term if it's larger than a certain size.
class TermSizeCompactingPolicy : public CompactingPolicy {
  public:
  // Compact terms at decision levels below compact_below level, that are larger than 
  // term_size.  Keep at least keep_terms recent terms.
  TermSizeCompactingPolicy(int compact_below_level, int term_size, int keep_terms);
  
  bool should_compact(int decision_level) const override;
  bool remove_term(int term_number, const cnf::Or& term) const override;
  virtual int keep_last() const override { return keep_terms_; }
  private:
  int compact_below_level_;
  int term_size_;
  int keep_terms_;
};

} // namespace tribblesat

#endif // SRC_SAT_COMPACTING_POLICY_H