// Copyright 2019 Google LLC
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.


#include "src/simplesat/bin_algebra/unary_op.h"

namespace simplesat
{
namespace binary {

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

std::set<std::string> UnaryOp::GetVariables() const {
  return inner_.GetVariables();
}

std::string UnaryOp::to_string() const {
    std::string inner = inner_.to_string();
    switch(op_type_) {
        case UnaryType::NOT:
            return "(! " + inner +" )";
        case UnaryType::NOP:
            return "( " + inner + " )";
    }
}

} // namespace binary
} //  simplesat
