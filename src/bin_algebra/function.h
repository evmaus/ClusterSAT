#ifndef SRC_FUNCTION_H
#define SRC_FUNCTION_H

#include "function.h"
#include "src/bin_algebra/variable_environment.h"
#include <string>
#include <set>

namespace tribblesat {
namespace binary {
enum NodeType {
  OP,
  ATOM,
  VARIABLE
};

class Function {
  public:
  virtual bool Evaluate(VariableEnvironment env) const = 0; //TODO:  Return a status or similar if we can't evaluate?
  virtual std::set<std::string> GetVariables() const = 0;
  virtual std::string to_string() const = 0;
  NodeType Type() const { return node_type_; };
  virtual ~Function() {};
  
  protected:
  Function(NodeType type) : node_type_(type) {}
  NodeType node_type_;
};
} // namespace binary
} // namespace tribblesat
#endif // SRC_FUNCTION_H