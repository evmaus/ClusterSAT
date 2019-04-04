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

#include "src/clustersat/utilities/dimacs_cnf_parser.h"

#include <string>
#include <iostream>

#include "absl/strings/str_split.h"

namespace clustersat {

OrTerm ParseLine(std::string line) {
  std::vector<std::string> line_contents = absl::StrSplit(line, ' ', absl::SkipEmpty());
  clustersat::OrTerm term;
  for (int j = 0; j < line_contents.size(); j++) {
    if (line_contents[j] == "0") {
      break;
    } else {
      int32_t var_index = stoi(line_contents[j]);
      clustersat::Variable v;
      v.set_id(var_index);
      *term.add_variables() = v;
    }
  }
  return term;
}

clustersat::AndTerm DiMacsParser::ParseCnf(std::istream& input) 
{
  std::string line;
  while ( getline (input,line) && line[0] == 'c') {
  }
  
  // Parse first line:  p cnf nvar nclause
  std::vector<std::string> line_contents = absl::StrSplit(line, ' ', absl::SkipEmpty());
  // Expectation:  line is in the form 'p cnf nvar nclause'
  uint32_t num_terms = std::stoi(line_contents[2]);
  uint32_t num_clauses = std::stoi(line_contents[3]);

  clustersat::AndTerm terms;
  for(int i = 0; i < num_clauses; i++) {
    if(!getline(input, line)){
      // TODO error
    }
    (*terms.add_terms()) = ParseLine(line);
  }

  return terms;
}

} // namespace clustersat