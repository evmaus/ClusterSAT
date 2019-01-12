#ifndef SRC_VARIABLE_ENVIRONMENT_H
#define SRC_VARIABLE_ENVIRONMENT_H

#include <map>

namespace tribblesat {
class VariableEnvironment {
  public:
  static VariableEnvironment Empty();

  bool Lookup(std::string variable_name);
  void Assign(std::string variable_name, bool value);

  private:
  VariableEnvironment();
  std::map<std::string, bool> variables_;
};
} // namespace tribblesat

#endif // SRC_VARIABLE_ENVIRONMENT_H