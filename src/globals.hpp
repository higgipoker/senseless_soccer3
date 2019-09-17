#pragma once

#include "ball.hpp"
#include "files.hpp"

#include <string>

namespace Globals {
inline const std::string GFX_FOLDER = Files::getWorkingDirectory() + "/gfx/";
inline Ball *ball = nullptr;
inline const int SHADOW_Z = 0;
}  // namespace Globals
