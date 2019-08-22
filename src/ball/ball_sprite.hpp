#pragma once

#include <gamelib3/graphics/sprite.hpp>

namespace senseless_soccer3 {

/**
 * @brief The BallSprite class
 */
class BallSprite : public gamelib3::Sprite {
 public:
  /**
   * @brief BallSprite
   * @param spritesheet
   * @param rows
   * @param cols
   */
  BallSprite(const std::string& spritesheet, int rows, int cols);
};

}  // namespace senseless_soccer3
