#include "src/parsers/dimacs_parser.h"

#include <vector>
#include <string>
#include <iostream>
#include "absl/strings/str_split.h"

#include "src/cnf/cnf_and_op.h"
#include "src/cnf/cnf_or_op.h"
#include "src/cnf/cnf_variable.h"
#include "src/common/log.h"

namespace tribblesat {

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
    LOG(LogLevel::VERBOSE, "Skipping line "+line);
  }
  
  LOG(LogLevel::VERBOSE, "Found starting line: "+line);
  // Parse first line:  p cnf nvar nclause
  std::vector<std::string> line_contents = absl::StrSplit(line, ' ', absl::SkipEmpty());
  // Expectation:  line is in the form 'p cnf nvar nclause'
  LOG(LogLevel::VERBOSE, "nvar " + line_contents[2]);
  uint32_t num_terms = std::stoi(line_contents[2]);
  LOG(LogLevel::VERBOSE, "nclause " + line_contents[3]);
  uint32_t num_clauses = std::stoi(line_contents[3]);
  std::list<cnf::Or> terms;
  for(int i = 0; i < num_clauses; i++) {
    if(!getline(input, line)){
      // TODO error
    }
    LOG(LogLevel::VERBOSE, "Parsing line: "+line);
    
    auto term = ParseLine(line);
    
    terms.push_back(term);

    LOG(LogLevel::VERBOSE, "Parsed: " + term.to_string());
  }
  cnf::And expr(terms);
  return expr;
}
} // namespace tribblesat