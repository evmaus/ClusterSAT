#ifndef SRC_PARSERS_DIMACS_PARSER_H
#define SRC_PARSERS_DIMACS_PARSER_H

#include "src/clustersat/protocol/cnf.grpc.pb.h"

#include <iostream>

namespace clustersat {

class DiMacsParser {
  public:
  clustersat::AndTerm ParseCnf(std::istream& input);
};


} // namespace clustersat
#endif // SRC_PARSERS_DIMACS_PARSER_H