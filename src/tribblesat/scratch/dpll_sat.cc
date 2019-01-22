#include "src/sat/dpll_sat.h"

#include <vector>
#include <string>
#include <chrono>
#include <future>
#include <iostream>

#include "src/common/log.h"

namespace tribblesat {

DPLLSatStrategy::DPLLSatStrategy(uint64_t timeout) 
: timeout_ms_(timeout)
{ }


cnf::VectorVariableEnvironment UnitPropagate(const cnf::And& term, cnf::VectorVariableEnvironment env) {
  while(term.has_unit(env) && !term.has_empty(env))
  {
    cnf::Or unit = term.next_unit(env);
    LOG(LogLevel::VERBOSE, "Identified unit: " + unit.to_string() + " " + env.to_string());
    cnf::Variable variable = unit.first_unassigned(env);
    auto state = variable.negated() ? cnf::VariableState::SFALSE : cnf::VariableState::STRUE;
    env.assign(variable.id(), state);
    LOG(LogLevel::VERBOSE, "Assigned " + variable.to_string() + " -> " + std::to_string(state));
  }
  return env;
}

SatResult DPLLRecursive(const cnf::And& term, std::atomic_bool& run, cnf::VectorVariableEnvironment env)
{
  if (run == false) 
  {
    return SatResult(SatResultType::UNKNOWN, nullptr);
  }

  cnf::VectorVariableEnvironment next_env = UnitPropagate(term, env);
  if (term.has_empty(next_env)) {
    LOG(LogLevel::VERBOSE, "Conflict found in term " + term.next_empty(env).to_string() + " with " + env.to_string());
    return SatResult(SatResultType::UNSAT, nullptr);
  }
  else if (term.satisfied(env)) {
    return SatResult(SatResultType::SAT, &env);
  } else {
    cnf::variable_id i = next_env.first_unbound();
    cnf::VariableState next_state = cnf::VariableEnvironment::RandomState();
    LOG(LogLevel::VERBOSE, "Choosing variable: " + std::to_string(i) 
      + " assigning state " + std::to_string(next_state));
    next_env.assign(i, next_state);
    auto result = DPLLRecursive(term, run, next_env);
    if (result.first == SatResultType::SAT) {
      return result;
    } else {
      next_env.assign(i, cnf::VariableEnvironment::Not(next_state));
      return DPLLRecursive(term, run, next_env);
    }
  }
}

SatResult DPLLSatStrategy::DetermineCnfSatInternal(
    const cnf::And& term, std::atomic_bool& run) const 
{
  LOG(LogLevel::VERBOSE, "DPLL Invoked On: " + term.to_string());
  cnf::VectorVariableEnvironment env(term.variable_count());
  return DPLLRecursive(term, run, env);
}

SatResult DPLLSatStrategy::DetermineCnfSat(const cnf::And& term) const 
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