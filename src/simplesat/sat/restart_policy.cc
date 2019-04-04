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

#include "src/simplesat/sat/restart_policy.h"

namespace simplesat {

GeometricRestartPolicy::GeometricRestartPolicy(double term, int start) 
  : current_conflicts_(start), term_(term)
{

}

bool GeometricRestartPolicy::should_restart(Stats& stats) {
  return stats.conflict_count() > current_conflicts_;
}

void GeometricRestartPolicy::step_restart() {
  current_conflicts_ = term_*current_conflicts_;
}

} // namespace simplesat