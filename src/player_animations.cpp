#include "player_animations.hpp"


// -----------------------------------------------------------------------------
// load_animation_frames
// -----------------------------------------------------------------------------
void load_animation_frames(Animation &anim, AnimationID id) {
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