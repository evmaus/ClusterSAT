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

#include "src/sat/brute_force_sat.h"

#include <vector>
#include <string>
#include <chrono>
#include <future>
#include <iostream>

namespace tribblesat {
BruteForceSatStrategy::BruteForceSatStrategy(uint64_t timeout_ms)
  : timeout_ms_(timeout_ms)
{
}

bool NextEnvironment(cnf::VariableEnvironment& env) {
  bool carry = true;
  for (uint32_t i = 0; i < env.count() && carry; i++) {
    if (env.lookup(i) == cnf::VariableState::SFALSE) {
      env.assign(i, cnf::VariableState::STRUE);
      carry = false;
    }
    else if (env.lookup(i) == cnf::VariableState::STRUE) {
      env.assign(i, cnf::VariableState::SFALSE);
      carry = true;
    }
  }
  return !carry;
}

SatResult BruteForceSatStrategy::DetermineCnfSatInternal(const cnf::And& term, std::atomic_bool& run) const 
{
  // Try "All false" first.
  cnf::VectorVariableEnvironment env(term.variable_count(), cnf::VariableState::SFALSE);
  bool has_next = true;
  while (has_next && run) {
    if (term.satisfied(env)) {
      return SatResult(SatResultType::SAT, &env);
    }
    has_next = NextEnvironment(env);
  }

  if (run == true)
  {
    // Return SAT if no SAT solution is found.
    return SatResult(SatResultType::UNSAT, nullptr);
  } 
  else 
  {
    return SatResult(SatResultType::UNKNOWN, nullptr);
  }
}

SatResult BruteForceSatStrategy::DetermineCnfSat(const cnf::And& term) const 
{
  std::atomic_bool run;
  run = true;
  auto future = std::async(
    std::launch::async, [this, &term, &run]() {
      return DetermineCnfSatInternal(term, run);
    }
  );
  if (timeout_ms_ != 0)
  {
    auto status = future.wait_for(std::chrono::milliseconds(timeout_ms_));
    if (status == std::future_status::timeout)
    {
      run = false;
      future.wait();
      return future.get();
    } 
    else 
    {
      return future.get();
    } 
  } else {
    future.wait();
    return future.get();
  }
}

} // namespace tribblesat