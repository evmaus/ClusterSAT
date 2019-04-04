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



#include "src/utility/status/statusor.h"

#include "src/utility/status/logging.h"

namespace util {
namespace internal {

void StatusOrHelper::Crash(const Status& status) {
  GOOGLE_LOG(FATAL) << "Attempting to fetch value instead of handling error "
                    << status.ToString();
}

}  // namespace internal
}  // namespace util
