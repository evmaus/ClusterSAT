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

VariableEnvironment GetAllFalseEnvironment(std::vector<std::string> variable_list)
{
  VariableEnvironment env = VariableEnvironment::Empty();
  for (const std::string var_name : variable_list){
    env.Assign(var_name, false);
  }
  return env;
}

bool NextEnvironment(VariableEnvironment& env) {
  bool carry = true;
  for (auto it = env.begin(); it != env.end() && carry; it++) {
    if (!it->second) {
      it->second = true;
      carry = false;
    }
    else if (it->second) {
      it->second = false;
      carry = true;
    }
  }
  return !carry;
}

SatResultType BruteForceSatStrategy::DetermineSatInternal(const Function& function, std::atomic_bool& run) const 
{
  std::vector<std::string> variable_list = function.GetUnboundVariables();

  // Try "All true" first.
  VariableEnvironment env = GetAllFalseEnvironment(variable_list);
  bool has_next = true;
  while (has_next && run) {
    if (function.Evaluate(env)) {
      return SatResultType::SAT;
    }
    has_next = NextEnvironment(env);
  }

  if (run == true)
  {
    // Return SAT if no SAT solution is found.
    return SatResultType::UNSAT;
  } else 
  {
    return SatResultType::UNKNOWN;
  }
}

SatResultType BruteForceSatStrategy::DetermineSat(const Function& function) const 
{
  std::atomic_bool run;
  run = true;
  auto future = std::async(
    std::launch::async, [this, &function, &run]() {
      return DetermineSatInternal(function, run);
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