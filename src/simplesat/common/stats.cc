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

#include "src/simplesat/common/stats.h"

#include <sstream>

namespace simplesat {

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
  counters_["total_variable_pick"] += std::chrono::duration_cast<
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

double Stats::conflict_count() {
  return counters_["conflicts"];
}

std::string Stats::to_string() {
  std::ostringstream stream;
  stream << "Stats: ";
  for (auto stat : counters_ ) {
    stream << stat.first << " : " << std::to_string(stat.second) << std::endl;
  }
  return stream.str();
}

} // namespace simplesat
