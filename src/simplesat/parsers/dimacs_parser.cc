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

#include "src/simplesat/parsers/dimacs_parser.h"

#include <vector>
#include <string>
#include <iostream>
#include "absl/strings/str_split.h"

#include <glog/logging.h>
#include "src/simplesat/cnf/cnf_and_op.h"
#include "src/simplesat/cnf/cnf_or_op.h"
#include "src/simplesat/cnf/cnf_variable.h"

namespace simplesat {

cnf::Or ParseLine(std::string line) {
  std::vector<std::string> line_contents = absl::StrSplit(line, ' ', absl::SkipEmpty());
  std::vector<cnf::Variable> variables;
  for (int j = 0; j < line_contents.size(); j++) {
    if (line_contents[j] == "0") {
      break;
    } else {
      int32_t var_index = stoi(line_contents[j]);
      if (var_index > 0){
        cnf::Variable f(var_index);
        variables.push_back(f);
      } else {
        cnf::Variable f(-var_index, true);
        variables.push_back(f);
      }
    }
  }
  cnf::Or expr(variables);
  return expr;
}

cnf::And DiMacsParser::ParseCnf(std::istream& input) {
  std::string line;
  while ( getline (input,line) && line[0] == 'c') {
    LOG(INFO) << "Skipping line " << line;
  }
  
  LOG(INFO) << "Found starting line: " << line;
  // Parse first line:  p cnf nvar nclause
  std::vector<std::string> line_contents = absl::StrSplit(line, ' ', absl::SkipEmpty());
  // Expectation:  line is in the form 'p cnf nvar nclause'
  LOG(INFO) << "nvar " << line_contents[2];
  //uint32_t num_terms = std::stoi(line_contents[2]);
  LOG(INFO) << "nclause " << line_contents[3];
  uint32_t num_clauses = std::stoi(line_contents[3]);
  std::list<cnf::Or> terms;
  for(int i = 0; i < num_clauses; i++) {
    if(!getline(input, line)){
      // TODO error
    }
    LOG(INFO) << "Parsing line: " << line;
    
    auto term = ParseLine(line);
    
    terms.push_back(term);

    LOG(INFO) << "Parsed: " << term.to_string();
  }
  cnf::And expr(terms);
  return expr;
}
} // namespace simplesat