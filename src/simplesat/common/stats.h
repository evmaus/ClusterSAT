
#ifndef SRC_SAT_CDCL_STATS_H
#define SRC_SAT_CDCL_STATS_H

#include <string>
#include <map>
#include <chrono>

namespace simplesat {

using Timestamp =
  std::chrono::high_resolution_clock::time_point;

class Stats {
  public:
  Stats() {};

  void StartSAT();
  void EndSAT();

  void StartBCP();
  void BCPClauses(int clauses);
  void EndBCP();

  void StartVariablePick();
  void EndVariablePick();

  void StartConflictLearning();
  void LearnConflictSize(int clause_size);
  void EndConflictLearning();

  void Conflict();
  double conflict_count();

  std::string to_string();

  private:
  std::map<std::string, double> counters_;
  Timestamp cdcl_start_;
  Timestamp cdcl_end_;
  Timestamp cdcl_current_bcp_;
  Timestamp cdcl_current_conflict_;
  Timestamp cdcl_current_variable_pick_;
  long cdcl_current_bcp_clauses_;
};

} // namespace simplesat
#endif // SRC_SAT_CDCL_STATS_H