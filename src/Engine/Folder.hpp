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
  /**
   * @brief Folder
   * @param in_path
   */
  Folder(const std::string &in_path);
  /**
   * @brief getPath
   * @return
   */
  const std::string getPath();
  /**
   * @brief getFileList
   * @return
   */
  const std::set<std::string> getFileList(bool in_refresh = false);

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
  /**
   * @brief WorkingFolder
   */
  WorkingFolder();
};

}  // namespace Engine
