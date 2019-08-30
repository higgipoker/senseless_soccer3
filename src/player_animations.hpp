#pragma once

#include "animation.hpp"

#include <SFML/Graphics/Sprite.hpp>

#include <map>
#include <vector>

using Anims = std::vector<int>;

// anim speed for all player anims
static const int player_frame_time = 10;

/**
 * @brief The AnimationID enum
 */
enum class PlayerAnimation {

  // standing
  StandEast,
  StandSouthEast,
  StandSouth,
  StandSouthWest,
  StandWest,
  StandNorthWest,
  StandNorth,
  StandNorthEast,

  // running
  RunEast,
  RunSouthEast,
  RunSouth,
  RunSouthWest,
  RunWest,
  RunNorthWest,
  RunNorth,
  RunNorthEast,

  // sliding
  SlideEast,
  SlideSouthEast,
  SlideSouth,
  SlideSouthWest,
  SlideWest,
  SlideNorthWest,
  SlideNorth,
  SlideNorthEast
};

// -----------------------------------------------------------------------------
// standing animations
// -----------------------------------------------------------------------------
inline Anims stand_east() { return Anims{1}; }
inline Anims stand_southeast() { return Anims{4}; }
inline Anims stand_south() { return Anims{7}; }
inline Anims stand_southwest() { return Anims{10}; }
inline Anims stand_west() { return Anims{13}; }
inline Anims stand_northwest() { return Anims{16}; }
inline Anims stand_north() { return Anims{19}; }
inline Anims stand_northeast() { return Anims{22}; }
// -----------------------------------------------------------------------------
// running animations
// -----------------------------------------------------------------------------
inline Anims run_east() { return Anims{0, 1}; }
inline Anims run_southeast() { return Anims{3, 5}; }
inline Anims run_south() { return Anims{6, 8}; }
inline Anims run_southwest() { return Anims{9, 11}; }
inline Anims run_west() { return Anims{12, 13}; }
inline Anims run_northwest() { return Anims{15, 17}; }
inline Anims run_north() { return Anims{18, 20}; }
inline Anims run_northeast() { return Anims{21, 23}; }
// -----------------------------------------------------------------------------
// sliding animations
// -----------------------------------------------------------------------------
inline Anims slide_east() { return Anims{24, 25, 26, 26}; }
inline Anims slide_southeast() { return Anims{27, 28, 29, 29}; }
inline Anims slide_south() { return Anims{30, 31, 32, 32}; }
inline Anims slide_southwest() { return Anims{33, 34, 35, 35}; }
inline Anims slide_west() { return Anims{36, 37, 38, 38}; }
inline Anims slide_northwest() { return Anims{39, 40, 41, 41}; }
inline Anims slide_north() { return Anims{42, 43, 44, 44}; }
inline Anims slide_northeast() { return Anims{45, 46, 47, 47}; }
/**
 * @brief load_animation_frames
 * @param anim
 * @param id
 */
void load_player_animation_frames(Animation &anim, PlayerAnimation id);
