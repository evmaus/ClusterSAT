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

#include "src/simplesat/sat/compacting_policy.h"

namespace simplesat {

/// Term Size compacting policy.
TermSizeCompactingPolicy::TermSizeCompactingPolicy(
    int compact_below_level, 
    int term_size, 
    int keep_terms)
  : compact_below_level_(compact_below_level), term_size_(term_size), keep_terms_(keep_terms)
{

}

bool TermSizeCompactingPolicy::should_compact(int decision_level) const {
  return decision_level <= compact_below_level_;
}

bool TermSizeCompactingPolicy::remove_term(int term_number, const cnf::Or& term) const {
  return term.count() > term_size_;
}
/// End Term Size compacting policy.

} // namespace simplesat