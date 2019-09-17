#pragma once

#include <string>

namespace Engine {
/**
 * @brief The Files class
 */
class Files {
 public:
  /**
   * @brief Files
   */
  Files();

  /**
   * @brief getWorkingDirectory
   * @return
   */
  static std::string getWorkingDirectory();
};

}  // namespace Engine
