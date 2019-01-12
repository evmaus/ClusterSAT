#ifndef SRC_FUNCTION_H
#define SRC_FUNCTION_H

#include "function.h"
#include "src/model/variable_environment.h"
#include <string>
#include <vector>

namespace tribblesat 
{
enum NodeType {
  OP,
  ATOM,
  VARIABLE
};

class Function {
  public:
  virtual bool Evaluate(VariableEnvironment env) const = 0; //TODO:  Return a status or similar if we can't evaluate?
  virtual std::vector<std::string> GetUnboundVariables() const = 0;
  NodeType Type() const { return node_type_; };
  virtual ~Function() {};
  
  protected:
  Function(NodeType type) : node_type_(type) {}
  NodeType node_type_;
};
} // namespace tribblesat
#endif // SRC_FUNCTION_H