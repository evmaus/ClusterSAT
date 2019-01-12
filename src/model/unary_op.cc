
#include "src/model/unary_op.h"

namespace tribblesat
{

UnaryOp::UnaryOp(UnaryType type, const Function& inner) : 
  Function(NodeType::OP),
  op_type_(type), 
  inner_(inner)
{ 
    
}

UnaryOp UnaryOp::Not(Function& unary)
{
    return UnaryOp(UnaryType::NOT, unary);
}

UnaryOp UnaryOp::Nop(Function& unary)
{
    return UnaryOp(UnaryType::NOP, unary);
}

bool UnaryOp::Evaluate(VariableEnvironment env) const
{
    switch(op_type_) {
        case UnaryType::NOT:
            return !inner_.Evaluate(env);
        case UnaryType::NOP:
            return inner_.Evaluate(env);
    }
}

std::vector<std::string> UnaryOp::GetUnboundVariables() const {
  return inner_.GetUnboundVariables();
}

} //  tribblesat
