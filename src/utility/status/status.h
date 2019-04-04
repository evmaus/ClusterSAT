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



#ifndef SRC_UTILITY_STATUS_STATUS_H_
#define SRC_UTILITY_STATUS_STATUS_H_

#include <iosfwd>
#include <string>

namespace util {
namespace error {
// These values must match error codes defined in google/rpc/code.proto.
enum Code {
  OK = 0,
  CANCELLED = 1,
  UNKNOWN = 2,
  INVALID_ARGUMENT = 3,
  DEADLINE_EXCEEDED = 4,
  NOT_FOUND = 5,
  ALREADY_EXISTS = 6,
  PERMISSION_DENIED = 7,
  UNAUTHENTICATED = 16,
  RESOURCE_EXHAUSTED = 8,
  FAILED_PRECONDITION = 9,
  ABORTED = 10,
  OUT_OF_RANGE = 11,
  UNIMPLEMENTED = 12,
  INTERNAL = 13,
  UNAVAILABLE = 14,
  DATA_LOSS = 15,
};
}  // namespace error

class Status {
 public:
  // Creates a "successful" status.
  Status();

  // Create a status in the canonical error space with the specified
  // code, and error message.  If "code == 0", error_message is
  // ignored and a Status object identical to Status::OK is
  // constructed.
  Status(error::Code error_code, std::string error_message);
  Status(const Status&);
  Status& operator=(const Status& x);
  ~Status() {}

  // Some pre-defined Status objects
  static const Status OK;             // Identical to 0-arg constructor
  static const Status CANCELLED;
  static const Status UNKNOWN;

  // Accessor
  bool ok() const {
    return error_code_ == error::OK;
  }
  int error_code() const {
    return error_code_;
  }
  error::Code code() const {
    return error_code_;
  }
  std::string error_message() const {
    return error_message_;
  }
  std::string message() const {
    return error_message_;
  }

  bool operator==(const Status& x) const;
  bool operator!=(const Status& x) const {
    return !operator==(x);
  }

  // Return a combination of the error code name and message.
  std::string ToString() const;

 private:
  error::Code error_code_;
  std::string error_message_;
};

// Prints a human-readable representation of 'x' to 'os'.
std::ostream& operator<<(std::ostream& os, const Status& x);

#define EXPECT_OK(value) EXPECT_TRUE((value).ok())

}  // namespace util

#endif  // SRC_UTILITY_STATUS_STATUS_H_
