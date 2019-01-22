
#include "src/tribblesat/common/utilities.h"

#include <glob.h>

namespace tribblesat {

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

} // namespace tribblesat