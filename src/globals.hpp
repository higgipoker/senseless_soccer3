#pragma once

#include "ball.hpp"

#include <gamelib3/utils/files.hpp>
#include <string>

namespace Globals {
inline const std::string GFX_FOLDER =
    gamelib3::Files::getWorkingDirectory() + "/gfx/";
}  // namespace Globals
