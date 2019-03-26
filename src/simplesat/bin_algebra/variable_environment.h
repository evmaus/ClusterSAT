#ifndef SRC_VARIABLE_ENVIRONMENT_H
#define SRC_VARIABLE_ENVIRONMENT_H

#include <map>
#include <string>

namespace simplesat {
namespace binary {
class VariableEnvironment {
  public:
  static VariableEnvironment Empty();

  bool Lookup(::std::string variable_name);
  void Assign(::std::string variable_name, bool value);
  
  ::std::map<std::string, bool>::iterator begin() { return variables_.begin(); }
  ::std::map<std::string, bool>::iterator end() { return variables_.end(); }

  private:
  VariableEnvironment();
  ::std::map<std::string, bool> variables_;
};
} // namespace binary
} // namespace simplesat

#endif // SRC_VARIABLE_ENVIRONMENT_H