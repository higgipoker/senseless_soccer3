#pragma once

#include "PlayerAnimations.hpp"

#include "Engine/Compass.hpp"
#include "Engine/Sprite.hpp"

#include <map>

/**
 * @brief The PlayerSprite class
 */
class PlayerSprite : public Engine::Sprite {
 public:
  /**
   * @brief PlayerSprite
   */
  PlayerSprite(const std::string &in_filename);
  /**
   * @brief setAnimation
   * @param in_type
   * @param in_direction
   */
  void setAnimation(PlayerAnimationType in_type,
                    Engine::Direction in_direction);

 private:
  AnimMap stand_animations;
  AnimMap run_animations;
  AnimMap slide_animations;
};
