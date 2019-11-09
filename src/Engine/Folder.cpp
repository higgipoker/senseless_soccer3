#include "Folder.hpp"

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
#include <array>
#include <iostream>

namespace Engine {
//
//
//
inline std::string getWorkingDirectory() {
  std::array<char, FILENAME_MAX> buff{};
  GetCurrentDir(static_cast<char *>(buff.data()), FILENAME_MAX);
  return (static_cast<char *>(buff.data()));
}
//
//
//
Folder::Folder(const std::string &in_path) : path(in_path) {read_files_and_folders();}
//
//
//
const std::string Folder::getPath(bool in_add_trailing_slash) {
  return in_add_trailing_slash ? path + "/" : path;
}
//
//
//
const std::set<std::string> Folder::getFileList(bool in_refresh) {
  if (in_refresh) {
    read_files_and_folders();
  }
  return files;
}
//
//
//
const std::set<std::string> Folder::getFolderList(bool in_refresh) {
  if (in_refresh) {
    read_files_and_folders();
  }
  return folders;
}
//
//
//
const std::set<std::string> Folder::getFileAndFolderList(bool in_refresh) {
  if (in_refresh) {
    read_files_and_folders();
  }
  return files_and_folders;
}
//
//
//
void Folder::changeDirectory(const std::string &in_dir) {
  path = in_dir;
  getFileList(true);
}
//
//
//
void Folder::read_files_and_folders(bool in_refresh, GetType in_type) {
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
        if (ent->d_type == DT_DIR) {
          // files.insert(path + "/" + ent->d_name);
          folders.insert(ent->d_name);
        } else {
          files.insert(ent->d_name);
        }
        files_and_folders.insert(ent->d_name);
      }
      closedir(dir);
    } else {
      std::cout << "Folder::getFileList> could not open directory: " << path
                << std::endl;
    }
  }
}
//
//
//
WorkingFolder::WorkingFolder() : Folder(getWorkingDirectory()) {}

}  // namespace Engine
