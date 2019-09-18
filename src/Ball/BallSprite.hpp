#pragma once

#include "Engine/Compass.hpp"
#include "Engine/Sprite.hpp"
#include "Engine/SpriteAnimation.hpp"

#include <map>

using Frames = std::vector<int>;
static const int BALL_ANIM_FRAME_TIME = 2;
//
// spritesheet layout defines
//
inline constexpr int BALL_FRAME_WIDTH = 32;
inline constexpr int BALL_FRAME_HEIGHT = 32;
inline constexpr int BALL_FRAMES = 7;
inline constexpr int BALL_START_ROW = 6;
inline constexpr int BALL_START_COL = 0;
inline constexpr int BALL_COLS = 24;
//
// rolling animation
//
inline Frames roll{0, 1, 2, 3, 4, 5, 6};

/**
 * @brief The BallSprite class
 */
class BallSprite : public Engine::Sprite {
 public:
  /**
   * @brief BallSprite
   */
  BallSprite(
      const std::string &in_filename,
      const Engine::SpriteSetDefinition in_def = Engine::SpriteSetDefinition{
          BALL_FRAME_WIDTH, BALL_FRAME_HEIGHT, BALL_FRAMES, BALL_START_ROW,
          BALL_START_COL, BALL_COLS});

 protected:
  Engine::SpriteAnimation roll_animation{BALL_ANIM_FRAME_TIME, roll};
};
