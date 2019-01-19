#include "src/common/stats.h"

#include <sstream>

namespace tribblesat {

void Stats::StartSAT() 
{
  cdcl_start_ = std::chrono::high_resolution_clock::now(); 
}

void Stats::EndSAT() 
{ 
  cdcl_end_ = std::chrono::high_resolution_clock::now();
  counters_["total_time"] = std::chrono::duration_cast<
        std::chrono::duration<double>>(cdcl_end_ - cdcl_start_).count();
}


void Stats::StartVariablePick() 
{
  cdcl_current_variable_pick_ = std::chrono::high_resolution_clock::now(); 
}

void Stats::EndVariablePick() 
{
  Timestamp end =  std::chrono::high_resolution_clock::now();
  counters_["total_variable_pick"] = std::chrono::duration_cast<
        std::chrono::duration<double>>(end - cdcl_current_variable_pick_).count();
}

void Stats::StartBCP() 
{ 
  cdcl_current_bcp_ = std::chrono::high_resolution_clock::now(); 
  cdcl_current_bcp_clauses_ = 0;
}

void Stats::BCPClauses(int clauses) {
  cdcl_current_bcp_clauses_ += clauses;
}

void Stats::EndBCP() 
{ 
  Timestamp end =  std::chrono::high_resolution_clock::now();
  auto timespan = std::chrono::duration_cast<
      std::chrono::duration<double>>(end - cdcl_current_bcp_);
  counters_["bcp_terms"] += cdcl_current_bcp_clauses_;
  counters_["bcp_time"] += timespan.count(); 
}


void Stats::StartConflictLearning() {
  cdcl_current_conflict_ = std::chrono::high_resolution_clock::now();
}
void Stats::LearnConflictSize(int clause_size) {
  counters_["conflict_total_size"] += clause_size;
}
void Stats::EndConflictLearning() {

  Timestamp end =  std::chrono::high_resolution_clock::now();
  auto timespan = std::chrono::duration_cast<
      std::chrono::duration<double>>(end - cdcl_current_conflict_);
  counters_["conflict_time"] += timespan.count(); 
}

void Stats::Conflict()
{ 
  counters_["conflicts"]++; 
}

std::string Stats::to_string() {
  std::ostringstream stream;
  stream << "Stats: ";
  for (auto stat : counters_ ) {
    stream << stat.first << " : " << std::to_string(stat.second) << std::endl;
  }
  return stream.str();
}

} // namespace tribblesat
