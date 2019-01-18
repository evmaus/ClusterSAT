#include "src/common/log.h"

#include <string>
#include <iostream>

namespace tribblesat {

LogLevel GLOBAL_LOG_LEVEL = LogLevel::ERROR;

void SET_LOG_LEVEL(LogLevel level) {
  GLOBAL_LOG_LEVEL = level;
}

std::string LevelToString(LogLevel level) {
  switch(level) {
    case LogLevel::INFORMATIONAL:
      return "INFO";
    case LogLevel::VERBOSE:
      return "VERBOSE";
    case LogLevel::ERROR:
      return "ERROR";
    case LogLevel::WARNING:
      return "WARNING";
  }
}

void LOG(LogLevel level, std::string output) {
  if( (int) level <= (int) GLOBAL_LOG_LEVEL) {
    std::cout << LevelToString(level) << ": " << output << std::endl;
  }
}

} // namespace tribblesat
