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

#ifndef SRC_SAT_RESTART_POLICY_H
#define SRC_SAT_RESTART_POLICY_H

#include "src/simplesat/common/stats.h"

namespace simplesat {

enum class RestartPolicyType {
  NONE,
  GEOMETRIC
};

class RestartPolicy {
  public:
  virtual ~RestartPolicy() { };
  virtual bool should_restart(Stats& stats) = 0;
  virtual void step_restart() = 0;
};

class NoRestartPolicy : public RestartPolicy {
  public:
  bool should_restart(Stats& stats) override { return false; }
  void step_restart() override { }
};


// Restart if we hit a certain number of conflicts.
class GeometricRestartPolicy : public RestartPolicy{
  public:
  GeometricRestartPolicy(double term, int start);
  bool should_restart(Stats& stats) override;
  void step_restart() override;

  private:
  double current_conflicts_;
  double term_;
};

} // namespace simplesat

#endif // SRC_SAT_RESTART_POLICY_H