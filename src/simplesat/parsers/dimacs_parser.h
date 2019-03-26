#ifndef SRC_PARSERS_DIMACS_PARSER_H
#define SRC_PARSERS_DIMACS_PARSER_H

#include "src/simplesat/cnf/cnf_and_op.h"

#include <iostream>

namespace simplesat {

class DiMacsParser {
  public:
  cnf::And ParseCnf(std::istream& input);
};


}
#endif // SRC_PARSERS_DIMACS_PARSER_H