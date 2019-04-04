/*
 * Copyright 2019 Google LLC
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

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