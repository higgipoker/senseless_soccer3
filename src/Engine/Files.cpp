#include "Files.hpp"

#ifdef _WIN32
#include <direct.h>
#include "windows/dirent.h"
#define GetCurrentDir _getcwd
#else
#include <unistd.h>
#define GetCurrentDir getcwd
#include <dirent.h>
#include <cstring>
#include <sys/types.h>
#include <cstdio>
#endif
#include <filesystem>
#include <iostream>
//#endif
namespace Engine{
//
//
//
Files::Files() {}
//
//
//
std::string Files::getWorkingDirectory() {
  std::array<char, FILENAME_MAX> buff{};
  auto unused = GetCurrentDir(static_cast<char *>(buff.data()), FILENAME_MAX);
  std::string current_working_dir(static_cast<char *>(buff.data()));
  return current_working_dir;
}
}
