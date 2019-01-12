#ifndef SRC_VARIABLE_H
#define SRC_VARIABLE_H

#include "src/model/function.h"
#include <string>

namespace tribblesat
{
class Variable : public Function {
  public:
  Variable(std::string name);
  bool Evaluate(VariableEnvironment env) const override; // TODO...
  std::vector<std::string> GetUnboundVariables() const override;
  
  std::string name() { return name_; }
  
  private:
  std::string name_;
};

} // namespace tribblesat
#endif