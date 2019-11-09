#pragma once

#include "PlayerAnimations.hpp"

#include "Engine/Compass.hpp"
#include "Engine/Sprite.hpp"

#include <map>

enum class TeamType;

// sprite frame constants
inline const int VERTICAL_OFFSET_TEAM1 = 0;
inline const int VERTICAL_OFFSET_TEAM2 = 96;
inline const int SHADOW_VERTICAL_OFFSET = 192;
inline const int FRAME_WIDTH = 32;
inline const int FRAME_HEIGHT = 32;
inline const int FRAMES = 72;
inline const int START_ROW = 0;
inline const int START_COL = 0;
inline const int COLS = 24;
//
//
//
inline const int SHADOW_START_ROW = 0;
//
//
//
class PlayerSprite : public Engine::Sprite {
 public:
  //
  //
  //
  PlayerSprite() { perspectivizable = true; };
  //
  //
  //
  PlayerSprite(
      const sf::Texture& in_texture, const TeamType in_team,
      Engine::SpriteSetDefinition in_def = Engine::SpriteSetDefinition{
          VERTICAL_OFFSET_TEAM1, FRAME_WIDTH, FRAME_HEIGHT, FRAMES, START_ROW,
          START_COL, COLS});
  //
  //
  //
  void setPlayerAnimation(PlayerAnimationType in_type,
                          Engine::Direction in_direction);
  //
  //
  //
 protected:
 private:
  AnimMap stand_animations;
  AnimMap run_animations;
  AnimMap slide_animations;
};
//
//
//
class PlayerShadowSprite : public PlayerSprite {
 public:
  //
  //
  //
  PlayerShadowSprite(
      const sf::Texture& in_texture,
      const Engine::SpriteSetDefinition in_def = Engine::SpriteSetDefinition{
          SHADOW_VERTICAL_OFFSET, FRAME_WIDTH, FRAME_HEIGHT, FRAMES,
          SHADOW_START_ROW, START_COL, COLS});
};
