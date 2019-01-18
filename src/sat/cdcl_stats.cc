#include "src/sat/cdcl_stats.h"

#include <sstream>

namespace tribblesat {

void CDCLStats::StartCDCL() 
{
  cdcl_start_ = std::chrono::high_resolution_clock::now(); 
}

void CDCLStats::EndCDCL() 
{ 
  cdcl_end_ = std::chrono::high_resolution_clock::now();
  counters_["total_time"] = std::chrono::duration_cast<
        std::chrono::duration<double>>(cdcl_end_ - cdcl_start_).count();
}


void CDCLStats::StartVariablePick() 
{
  cdcl_current_variable_pick_ = std::chrono::high_resolution_clock::now(); 
}

void CDCLStats::EndVariablePick() 
{
  Timestamp end =  std::chrono::high_resolution_clock::now();
  counters_["total_variable_pick"] = std::chrono::duration_cast<
        std::chrono::duration<double>>(end - cdcl_current_variable_pick_).count();
}

void CDCLStats::StartBCP() 
{ 
  cdcl_current_bcp_ = std::chrono::high_resolution_clock::now(); 
  cdcl_current_bcp_clauses_ = 0;
}

void CDCLStats::BCPClauses(int clauses) {
  cdcl_current_bcp_clauses_ += clauses;
}

void CDCLStats::EndBCP() 
{ 
  Timestamp end =  std::chrono::high_resolution_clock::now();
  auto timespan = std::chrono::duration_cast<
      std::chrono::duration<double>>(end - cdcl_current_bcp_);
  counters_["bcp_time"] += timespan.count(); 
}


void CDCLStats::StartConflictLearning() {
  cdcl_current_conflict_ = std::chrono::high_resolution_clock::now();
}
void CDCLStats::LearnConflictSize(int clause_size) {
  counters_["bcp_conflict_total_size"] += clause_size;
}
void CDCLStats::EndConflictLearning() {

  Timestamp end =  std::chrono::high_resolution_clock::now();
  auto timespan = std::chrono::duration_cast<
      std::chrono::duration<double>>(end - cdcl_current_conflict_);
  counters_["conflict_time"] += timespan.count(); 
}

void CDCLStats::Conflict()
{ 
  counters_["conflicts"]++; 
}

std::string CDCLStats::to_string() {
  std::ostringstream stream;
  stream << "Stats: ";
  for (auto stat : counters_ ) {
    stream << stat.first << " : " << std::to_string(stat.second) << std::endl;
  }
  return stream.str();
}

} // namespace tribblesat
