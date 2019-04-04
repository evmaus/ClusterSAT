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



#ifndef SRC_UTILITY_STATUS_LOGGING_H_
#define SRC_UTILITY_STATUS_LOGGING_H_

#include <string>
#include <cstdint>

// ===================================================================
// emulates google3/base/logging.h

namespace util {

enum LogLevel {
  LOGLEVEL_INFO,     // Informational.  This is never actually used by
                     // libprotobuf.
  LOGLEVEL_WARNING,  // Warns about issues that, although not technically a
                     // problem now, could cause problems in the future.  For
                     // example, a // warning will be printed when parsing a
                     // message that is near the message size limit.
  LOGLEVEL_ERROR,    // An error occurred which should never happen during
                     // normal use.
  LOGLEVEL_FATAL,    // An error occurred from which the library cannot
                     // recover.  This usually indicates a programming error
                     // in the code which calls the library, especially when
                     // compiled in debug mode.

#ifdef NDEBUG
  LOGLEVEL_DFATAL = LOGLEVEL_ERROR
#else
  LOGLEVEL_DFATAL = LOGLEVEL_FATAL
#endif
};

class Status;
namespace internal {

class LogFinisher;

class LogMessage {
 public:
  LogMessage(LogLevel level, const char* filename, int line);
  ~LogMessage();

  LogMessage& operator<<(const std::string& value);
  LogMessage& operator<<(const char* value);
  LogMessage& operator<<(char value);
  LogMessage& operator<<(int value);
  LogMessage& operator<<(long value);
  LogMessage& operator<<(unsigned long value);
  LogMessage& operator<<(double value);
  LogMessage& operator<<(void* value);
  LogMessage& operator<<(const Status& status);

 private:
  friend class LogFinisher;
  void Finish();

  LogLevel level_;
  const char* filename_;
  int line_;
  std::string message_;
};

// Used to make the entire "LOG(BLAH) << etc." expression have a void return
// type and print a newline after each message.
class LogFinisher {
 public:
  void operator=(LogMessage& other);
};

template<typename T>
bool IsOk(T status) { return status.ok(); }
template<>
inline bool IsOk(bool status) { return status; }

}  // namespace internal

// Undef everything in case we're being mixed with some other Google library
// which already defined them itself.  Presumably all Google libraries will
// support the same syntax for these so it should not be a big deal if they
// end up using our definitions instead.
#undef GOOGLE_LOG
#undef GOOGLE_LOG_IF

#undef GOOGLE_CHECK
#undef GOOGLE_CHECK_OK
#undef GOOGLE_CHECK_EQ
#undef GOOGLE_CHECK_NE
#undef GOOGLE_CHECK_LT
#undef GOOGLE_CHECK_LE
#undef GOOGLE_CHECK_GT
#undef GOOGLE_CHECK_GE
#undef GOOGLE_CHECK_NOTNULL

#undef GOOGLE_DLOG
#undef GOOGLE_DCHECK
#undef GOOGLE_DCHECK_OK
#undef GOOGLE_DCHECK_EQ
#undef GOOGLE_DCHECK_NE
#undef GOOGLE_DCHECK_LT
#undef GOOGLE_DCHECK_LE
#undef GOOGLE_DCHECK_GT
#undef GOOGLE_DCHECK_GE

#define GOOGLE_LOG(LEVEL)                                                 \
  ::util::internal::LogFinisher() =                           \
    ::util::internal::LogMessage(                             \
      ::util::LOGLEVEL_##LEVEL, __FILE__, __LINE__)
#define GOOGLE_LOG_IF(LEVEL, CONDITION) \
  !(CONDITION) ? (void)0 : GOOGLE_LOG(LEVEL)

#define GOOGLE_CHECK(EXPRESSION) \
  GOOGLE_LOG_IF(FATAL, !(EXPRESSION)) << "CHECK failed: " #EXPRESSION ": "
#define GOOGLE_CHECK_OK(A) GOOGLE_CHECK(::util::internal::IsOk(A))
#define GOOGLE_CHECK_EQ(A, B) GOOGLE_CHECK((A) == (B))
#define GOOGLE_CHECK_NE(A, B) GOOGLE_CHECK((A) != (B))
#define GOOGLE_CHECK_LT(A, B) GOOGLE_CHECK((A) <  (B))
#define GOOGLE_CHECK_LE(A, B) GOOGLE_CHECK((A) <= (B))
#define GOOGLE_CHECK_GT(A, B) GOOGLE_CHECK((A) >  (B))
#define GOOGLE_CHECK_GE(A, B) GOOGLE_CHECK((A) >= (B))

namespace internal {
template<typename T>
T* CheckNotNull(const char* /* file */, int /* line */,
                const char* name, T* val) {
  if (val == nullptr) {
    GOOGLE_LOG(FATAL) << name;
  }
  return val;
}
}  // namespace internal
#define GOOGLE_CHECK_NOTNULL(A) \
  ::google::protobuf::internal::CheckNotNull(\
      __FILE__, __LINE__, "'" #A "' must not be nullptr", (A))

#ifdef NDEBUG

#define GOOGLE_DLOG(LEVEL) GOOGLE_LOG_IF(LEVEL, false)

#define GOOGLE_DCHECK(EXPRESSION) while(false) GOOGLE_CHECK(EXPRESSION)
#define GOOGLE_DCHECK_OK(E) GOOGLE_DCHECK(::util::internal::IsOk(E))
#define GOOGLE_DCHECK_EQ(A, B) GOOGLE_DCHECK((A) == (B))
#define GOOGLE_DCHECK_NE(A, B) GOOGLE_DCHECK((A) != (B))
#define GOOGLE_DCHECK_LT(A, B) GOOGLE_DCHECK((A) <  (B))
#define GOOGLE_DCHECK_LE(A, B) GOOGLE_DCHECK((A) <= (B))
#define GOOGLE_DCHECK_GT(A, B) GOOGLE_DCHECK((A) >  (B))
#define GOOGLE_DCHECK_GE(A, B) GOOGLE_DCHECK((A) >= (B))

#else  // NDEBUG

#define GOOGLE_DLOG GOOGLE_LOG

#define GOOGLE_DCHECK    GOOGLE_CHECK
#define GOOGLE_DCHECK_OK GOOGLE_CHECK_OK
#define GOOGLE_DCHECK_EQ GOOGLE_CHECK_EQ
#define GOOGLE_DCHECK_NE GOOGLE_CHECK_NE
#define GOOGLE_DCHECK_LT GOOGLE_CHECK_LT
#define GOOGLE_DCHECK_LE GOOGLE_CHECK_LE
#define GOOGLE_DCHECK_GT GOOGLE_CHECK_GT
#define GOOGLE_DCHECK_GE GOOGLE_CHECK_GE

#endif  // !NDEBUG

typedef void LogHandler(LogLevel level, const char* filename, int line,
                        const std::string& message);

// The protobuf library sometimes writes warning and error messages to
// stderr.  These messages are primarily useful for developers, but may
// also help end users figure out a problem.  If you would prefer that
// these messages be sent somewhere other than stderr, call SetLogHandler()
// to set your own handler.  This returns the old handler.  Set the handler
// to nullptr to ignore log messages (but see also LogSilencer, below).
//
// Obviously, SetLogHandler is not thread-safe.  You should only call it
// at initialization time, and probably not from library code.  If you
// simply want to suppress log messages temporarily (e.g. because you
// have some code that tends to trigger them frequently and you know
// the warnings are not important to you), use the LogSilencer class
// below.
LogHandler* SetLogHandler(LogHandler* new_func);

// Create a LogSilencer if you want to temporarily suppress all log
// messages.  As long as any LogSilencer objects exist, non-fatal
// log messages will be discarded (the current LogHandler will *not*
// be called).  Constructing a LogSilencer is thread-safe.  You may
// accidentally suppress log messages occurring in another thread, but
// since messages are generally for debugging purposes only, this isn't
// a big deal.  If you want to intercept log messages, use SetLogHandler().
class LogSilencer {
 public:
  LogSilencer();
  ~LogSilencer();
};

}  // namespace util

#endif  // SRC_UTILITY_STATUS_LOGGING_H_
