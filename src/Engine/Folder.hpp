#pragma once

#include <set>
#include <string>

namespace Senseless {
enum class GetType { Files, Folders, All };

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
  const std::string getPath(bool in_add_trailing_slash = false);
  //
  //
  //
  const std::set<std::string> getFileList(bool in_refresh = false);
  //
  //
  //
  const std::set<std::string> getFolderList(bool in_refresh = false);
  //
  //
  //
  const std::set<std::string> getFileAndFolderList(bool in_refresh = false);
  //
  //
  //
  void changeDirectory(const std::string &in_dir);

 protected:
  /// full path of this folder
  std::string path;
  /// save the list of files in this folder for convenience
  std::set<std::string> files;
  /// save the list of folders
  std::set<std::string> folders;
  /// union of the above
  std::set<std::string> files_and_folders;

  //
  //
  //
  void read_files_and_folders(bool in_refresh = false);
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

}  // namespace Senseless
