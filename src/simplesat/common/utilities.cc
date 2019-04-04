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


#include "src/simplesat/common/utilities.h"

#include <glob.h>

namespace simplesat {

// Based on a Stack Overflow
// answer to question:   https://stackoverflow.com/questions/612097/how-can-i-get-the-list-of-files-in-a-directory-using-c-or-c
// Answer provided by Chris Redford:  https://stackoverflow.com/users/130427/chris-redford
// 
std::vector<std::string> file_glob(std::string path) {
  glob_t glob_result;
  int ret = glob(path.c_str(),GLOB_TILDE,NULL,&glob_result);
  std::vector<std::string> files;
  if (ret != 0) return files;
  for(unsigned int i=0;i<glob_result.gl_pathc;++i){
      files.push_back(std::string(glob_result.gl_pathv[i]));
  }
  globfree(&glob_result);
  return files;
}

} // namespace simplesat