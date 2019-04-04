/*
 * Copyright 2019 Google LLC
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */


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