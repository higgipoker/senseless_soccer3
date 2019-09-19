#pragma once

#include "PlayerAnimations.hpp"

#include "Engine/Compass.hpp"
#include "Engine/Sprite.hpp"

#include <map>

// sprite frame constants
inline constexpr int FRAME_WIDTH = 32;
inline constexpr int FRAME_HEIGHT = 32;
inline constexpr int FRAMES = 72;
inline constexpr int START_ROW = 0;
inline constexpr int START_COL = 0;
inline constexpr int COLS = 24;

inline constexpr int SHADOW_START_ROW = 3;

/**
 * @brief The PlayerSprite class
 */
class PlayerSprite : public Engine::Sprite {
 public:
  /**
   * @brief PlayerSprite
   */
  PlayerSprite() = default;
  /**
   * @brief PlayerSprite
   * @param in_filename
   * @param in_def
   */
  PlayerSprite(
      std::shared_ptr<sf::Texture> in_texture,
      const Engine::SpriteSetDefinition in_def = Engine::SpriteSetDefinition{
          FRAME_WIDTH, FRAME_HEIGHT, FRAMES, START_ROW, START_COL, COLS});
  /**
   * @brief setAnimation
   * @param in_type
   * @param in_direction
   */
  void setAnimation(PlayerAnimationType in_type,
                    Engine::Direction in_direction);



 protected:
 private:
  AnimMap stand_animations;
  AnimMap run_animations;
  AnimMap slide_animations;
};

/**
 * @brief The PlayerShadowSprite class
 */
class PlayerShadowSprite : public PlayerSprite {
 public:
  /**
   * @brief PlayerShadowSprite
   * @param in_filename
   */
  PlayerShadowSprite(std::shared_ptr<sf::Texture> in_texture,
                     const Engine::SpriteSetDefinition in_def =
                         Engine::SpriteSetDefinition{FRAME_WIDTH, FRAME_HEIGHT,
                                                     FRAMES, SHADOW_START_ROW,
                                                     START_COL, COLS});
};
