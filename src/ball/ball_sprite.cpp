#include "ball_sprite.hpp"

namespace senseless_soccer3 {
BallSprite::BallSprite(const std::string& spritesheet, int rows, int cols)
    : gamelib3::Sprite(spritesheet, rows, cols) {}

}  // namespace senseless_soccer3
