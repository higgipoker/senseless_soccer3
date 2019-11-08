#pragma once
#include "Engine/Folder.hpp"
namespace Engine {
//
//
//
class BaseFactory {
 public:
 protected:
  WorkingFolder working_folder;
  Folder graphics_folder{working_folder.getPath() + "/gfx"};
};
}  // namespace Engine
