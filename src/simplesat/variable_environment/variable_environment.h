#ifndef SRC_CNF_CNF_VARIABLE_ENVIRONMENT_H
#define SRC_CNF_CNF_VARIABLE_ENVIRONMENT_H

#include <vector>

namespace simplesat {
typedef int64_t variable_id;

enum VariableState {
  STRUE,
  SFALSE,
  SUNBOUND
};

using VariableRecommendation = std::pair<variable_id, VariableState>;

class VariableEnvironment {
  public:
  virtual ~VariableEnvironment() {};

  virtual void assign(variable_id variable, VariableState value) = 0;
  virtual VariableState lookup(variable_id variable) const = 0;
  virtual variable_id count() const = 0;
  virtual VariableRecommendation next_unbound() const = 0;
  virtual std::string to_string() const = 0;

  static VariableState Not(VariableState state);
  static VariableState RandomState();
  static std::string StateToString(VariableState state);

  virtual std::vector<int> assignments_by_id() const = 0;
  
};

} // namespace simplesat
#endif // SRC_CNF_CNF_VARIABLE_ENVIRONMENT_H