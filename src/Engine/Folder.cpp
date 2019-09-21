#include "Folder.hpp"
#include "includes.hpp"

#ifdef _WIN32
#include <direct.h>
#include "Windows/dirent.h"
#define GetCurrentDir _getcwd
#else
#include <unistd.h>
#define GetCurrentDir getcwd
#include <dirent.h>
#include <sys/types.h>
#include <cstdio>
#include <cstring>
#endif
#include <filesystem>
//#endif
namespace Engine {
//
//
//
inline std::string getWorkingDirectory() {
  std::array<char, FILENAME_MAX> buff{};
  auto unused = GetCurrentDir(static_cast<char *>(buff.data()), FILENAME_MAX);
  std::cout << unused << std::endl;
  return (static_cast<char *>(buff.data()));
}
//
//
//
Folder::Folder(const std::string &in_path) : path(in_path) {}
//
//
//
const std::string Folder::getPath() { return path; }
//
//
//
const std::set<std::string> Folder::getFileList(bool in_refresh) {
  if (in_refresh || files.empty()) {
    // first call, or refresh requested
    files.clear();
    DIR *dir;
    struct dirent *ent;
    if ((dir = opendir(path.c_str())) != nullptr) {
      while ((ent = readdir(dir)) != nullptr) {
        if (strncmp(ent->d_name, ".", sizeof(ent->d_name)) == 0 ||
            strncmp(ent->d_name, "..", sizeof(ent->d_name)) == 0)
          continue;
        std::cout << path + "/" + ent->d_name << std::endl;
        files.insert(path + "/" + ent->d_name);
      }
      closedir(dir);
    } else {
      std::cout << "Folder::getFileList > could not open directory: " << path
                << std::endl;
    }
  }
  return files;
}
//
//
//
WorkingFolder::WorkingFolder() : Folder(getWorkingDirectory()) {}

}  // namespace Engine
