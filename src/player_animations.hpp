#pragma once

#include "animation.hpp"

#include <SFML/Graphics/Sprite.hpp>

#include <map>
#include <vector>

namespace PlayerAnimations {

// anim speed for all player anims
static const int frame_time = 10;

/**
 * @brief The AnimationID enum
 */
enum class AnimationID {

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
static std::vector<int> stand_east() { return std::vector<int>{1}; }
static std::vector<int> stand_southeast() { return std::vector<int>{4}; }
static std::vector<int> stand_south() { return std::vector<int>{7}; }
static std::vector<int> stand_southwest() { return std::vector<int>{10}; }
static std::vector<int> stand_west() { return std::vector<int>{13}; }
static std::vector<int> stand_northwest() { return std::vector<int>{16}; }
static std::vector<int> stand_north() { return std::vector<int>{19}; }
static std::vector<int> stand_northeast() { return std::vector<int>{22}; }

// -----------------------------------------------------------------------------
// running animations
// -----------------------------------------------------------------------------
static std::vector<int> run_east() { return std::vector<int>{0, 1}; }
static std::vector<int> run_southeast() { return std::vector<int>{3, 5}; }
static std::vector<int> run_south() { return std::vector<int>{6, 8}; }
static std::vector<int> run_southwest() { return std::vector<int>{9, 11}; }
static std::vector<int> run_west() { return std::vector<int>{12, 13}; }
static std::vector<int> run_northwest() { return std::vector<int>{15, 17}; }
static std::vector<int> run_north() { return std::vector<int>{18, 20}; }
static std::vector<int> run_northeast() { return std::vector<int>{21, 23}; }

// -----------------------------------------------------------------------------
// sliding animations
// -----------------------------------------------------------------------------
static std::vector<int> slide_east() {
  return std::vector<int>{24, 25, 26, 26};
}
static std::vector<int> slide_southeast() {
  return std::vector<int>{27, 28, 29, 29};
}
static std::vector<int> slide_south() {
  return std::vector<int>{30, 31, 32, 32};
}
static std::vector<int> slide_southwest() {
  return std::vector<int>{33, 34, 35, 35};
}
static std::vector<int> slide_west() {
  return std::vector<int>{36, 37, 38, 38};
}
static std::vector<int> slide_northwest() {
  return std::vector<int>{39, 40, 41, 41};
}

static std::vector<int> slide_north() {
  return std::vector<int>{42, 43, 44, 44};
}
static std::vector<int> slide_northeast() {
  return std::vector<int>{45, 46, 47, 47};
}

// -----------------------------------------------------------------------------
// load_animation_frames
// -----------------------------------------------------------------------------
inline void load_animation_frames(Animation &anim, AnimationID id) {
  std::vector<int> frames;
  switch (id) {
    case AnimationID::RunEast:
      frames = run_east();
      break;
    case AnimationID::RunSouthEast:
      frames = run_southeast();
      break;
    case AnimationID::RunSouth:
      frames = run_south();
      break;
    case AnimationID::RunSouthWest:
      frames = run_southwest();
      break;
    case AnimationID::RunWest:
      frames = run_west();
      break;
    case AnimationID::RunNorthWest:
      frames = run_northwest();
      break;
    case AnimationID::RunNorth:
      frames = run_north();
      break;
    case AnimationID::RunNorthEast:
      frames = run_northeast();
      break;
  }

  // inits the anim with frame time and list of frames
  init(anim, frame_time, frames);
}

}  // namespace PlayerAnimations
