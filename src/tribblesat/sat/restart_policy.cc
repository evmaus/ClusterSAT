#include "src/tribblesat/sat/restart_policy.h"

namespace tribblesat {

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

} // namespace tribblesat