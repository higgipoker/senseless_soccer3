#pragma once

#include <set>
#include <string>

namespace Engine {
/**
 * @brief The Folder class
 */
class Folder {
 public:
  Folder() = default;
  //
  //
  //
  Folder(const std::string &in_path);
  //
  //
  //
  const std::string getPath();
  //
  //
  //
  const std::set<std::string> getFileList(bool in_refresh = false);
  //
  //
  //
  void changeDirectory(const std::string &in_dir);

 protected:
  /// full path of this folder
  std::string path;
  /// save the list of files in this folder for convenience
  std::set<std::string> files;
};
/**
 * @brief The WorkingFolder class
 */
class WorkingFolder : public Folder {
 public:
  //
  //
  //
  WorkingFolder();
};

}  // namespace Engine
