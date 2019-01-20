#ifndef SRC_SAT_RESTART_POLICY_H
#define SRC_SAT_RESTART_POLICY_H

#include "src/common/stats.h"

namespace tribblesat {

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

} // namespace tribblesat

#endif // SRC_SAT_RESTART_POLICY_H