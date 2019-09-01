#pragma once
#include <set>
#include <string>

/**
 * @brief The Files class
 */
class Files {
 public:
  /**
   * @brief getWorkingDirectory
   * @return
   */
  static std::string getWorkingDirectory();

  /**
   * @brief getFilesInFolder
   * @param folder
   * @return
   */
  static std::set<std::string> getFilesInFolder(std::string folder);
};
