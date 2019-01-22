#ifndef SRC_SAT_LOG_H
#define SRC_SAT_LOG_H

#include <string>

namespace tribblesat {
enum LogLevel {
  ERROR,
  WARNING,
  INFORMATIONAL,
  VERBOSE,
};

void SET_LOG_LEVEL(LogLevel level);
void LOG(LogLevel level, std::string string);

} // namespace tribblesat

#endif

