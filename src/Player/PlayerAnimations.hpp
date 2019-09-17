#pragma once

#include "Engine/Compass.hpp"
#include "Engine/SpriteAnimation.hpp"

#include <map>
#include <vector>

/// easier to read
using Anims = std::vector<int>;
using AnimMap = std::map<Engine::Direction, Engine::SpriteAnimation>;
/// anim speed for all player anims
static const int PLAYER_ANIM_FRAME_TIME = 10;
/**
 * @brief The PlayerAnimationType enum
 */
enum class PlayerAnimationType { Stand, Run, Slide };
//
// standing animations
//
inline Anims stand_east{1};
inline Anims stand_southeast{4};
inline Anims stand_south{7};
inline Anims stand_southwest{10};
inline Anims stand_west{13};
inline Anims stand_northwest{16};
inline Anims stand_north{19};
inline Anims stand_northeast{22};
//
// running animations
//
inline Anims run_east{0, 1};
inline Anims run_southeast{3, 5};
inline Anims run_south{6, 8};
inline Anims run_southwest{9, 11};
inline Anims run_west{12, 13};
inline Anims run_northwest{15, 17};
inline Anims run_north{18, 20};
inline Anims run_northeast{21, 23};
//
// sliding animations
//
inline Anims slide_east{24, 25, 26, 26};
inline Anims slide_southeast{27, 28, 29, 29};
inline Anims slide_south{30, 31, 32, 32};
inline Anims slide_southwest{33, 34, 35, 35};
inline Anims slide_west{36, 37, 38, 38};
inline Anims slide_northwest{39, 40, 41, 41};
inline Anims slide_north{42, 43, 44, 44};
inline Anims slide_northeast{45, 46, 47, 47};
//
//
//
inline void populateStandAnimations(AnimMap &out_stand_animations) {
  out_stand_animations.insert(
      {Engine::Direction::EAST,
       Engine::SpriteAnimation(PLAYER_ANIM_FRAME_TIME, stand_east)});
  out_stand_animations.insert(
      {Engine::Direction::WEST,
       Engine::SpriteAnimation(PLAYER_ANIM_FRAME_TIME, stand_west)});
  out_stand_animations.insert(
      {Engine::Direction::NORTH,
       Engine::SpriteAnimation(PLAYER_ANIM_FRAME_TIME, stand_north)});
  out_stand_animations.insert(
      {Engine::Direction::SOUTH,
       Engine::SpriteAnimation(PLAYER_ANIM_FRAME_TIME, stand_south)});
  out_stand_animations.insert(
      {Engine::Direction::NORTH_EAST,
       Engine::SpriteAnimation(PLAYER_ANIM_FRAME_TIME, stand_northeast)});
  out_stand_animations.insert(
      {Engine::Direction::NORTH_WEST,
       Engine::SpriteAnimation(PLAYER_ANIM_FRAME_TIME, stand_northwest)});
  out_stand_animations.insert(
      {Engine::Direction::SOUTH_EAST,
       Engine::SpriteAnimation(PLAYER_ANIM_FRAME_TIME, stand_southeast)});
  out_stand_animations.insert(
      {Engine::Direction::SOUTH_WEST,
       Engine::SpriteAnimation(PLAYER_ANIM_FRAME_TIME, stand_southwest)});
}
//
//
//
inline void populateRunAnimations(AnimMap &out_run_animations) {
  out_run_animations.insert(
      {Engine::Direction::EAST,
       Engine::SpriteAnimation(PLAYER_ANIM_FRAME_TIME, run_east)});
  out_run_animations.insert(
      {Engine::Direction::WEST,
       Engine::SpriteAnimation(PLAYER_ANIM_FRAME_TIME, run_west)});
  out_run_animations.insert(
      {Engine::Direction::NORTH,
       Engine::SpriteAnimation(PLAYER_ANIM_FRAME_TIME, run_north)});
  out_run_animations.insert(
      {Engine::Direction::SOUTH,
       Engine::SpriteAnimation(PLAYER_ANIM_FRAME_TIME, run_south)});
  out_run_animations.insert(
      {Engine::Direction::NORTH_EAST,
       Engine::SpriteAnimation(PLAYER_ANIM_FRAME_TIME, run_northeast)});
  out_run_animations.insert(
      {Engine::Direction::NORTH_WEST,
       Engine::SpriteAnimation(PLAYER_ANIM_FRAME_TIME, run_northwest)});
  out_run_animations.insert(
      {Engine::Direction::SOUTH_EAST,
       Engine::SpriteAnimation(PLAYER_ANIM_FRAME_TIME, run_southeast)});
  out_run_animations.insert(
      {Engine::Direction::SOUTH_WEST,
       Engine::SpriteAnimation(PLAYER_ANIM_FRAME_TIME, run_southwest)});
}
//
//
//
inline void populateSlideAnimations(AnimMap &out_slide_animations) {
  out_slide_animations.insert(
      {Engine::Direction::EAST,
       Engine::SpriteAnimation(PLAYER_ANIM_FRAME_TIME, slide_east)});
  out_slide_animations.insert(
      {Engine::Direction::WEST,
       Engine::SpriteAnimation(PLAYER_ANIM_FRAME_TIME, slide_west)});
  out_slide_animations.insert(
      {Engine::Direction::NORTH,
       Engine::SpriteAnimation(PLAYER_ANIM_FRAME_TIME, slide_north)});
  out_slide_animations.insert(
      {Engine::Direction::SOUTH,
       Engine::SpriteAnimation(PLAYER_ANIM_FRAME_TIME, slide_south)});
  out_slide_animations.insert(
      {Engine::Direction::NORTH_EAST,
       Engine::SpriteAnimation(PLAYER_ANIM_FRAME_TIME, slide_northeast)});
  out_slide_animations.insert(
      {Engine::Direction::NORTH_WEST,
       Engine::SpriteAnimation(PLAYER_ANIM_FRAME_TIME, slide_northwest)});
  out_slide_animations.insert(
      {Engine::Direction::SOUTH_EAST,
       Engine::SpriteAnimation(PLAYER_ANIM_FRAME_TIME, slide_southeast)});
  out_slide_animations.insert(
      {Engine::Direction::SOUTH_WEST,
       Engine::SpriteAnimation(PLAYER_ANIM_FRAME_TIME, slide_southwest)});
}
