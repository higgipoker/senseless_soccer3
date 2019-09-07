#pragma once

#include "ball.hpp"
#include "files.hpp"

#include <string>

namespace Globals {
inline const std::string GFX_FOLDER = Files::getWorkingDirectory() + "/gfx/";
inline Ball *ball = nullptr;
}  // namespace Globals
