#ifndef SRC_VARIABLE_H
#define SRC_VARIABLE_H

#include "src/simplesat/bin_algebra/function.h"
#include <string>

namespace simplesat {
namespace binary {
class Variable : public Function {
  public:
  Variable(::std::string name);
  bool Evaluate(VariableEnvironment env) const override;
  ::std::set<std::string> GetVariables() const override;
  ::std::string to_string() const override;
  ::std::string name() { return name_; }
  
  private:
  std::string name_;
};
} // namespace binary
} // namespace simplesat
#endif