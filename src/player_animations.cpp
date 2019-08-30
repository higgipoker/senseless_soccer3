#include "player_animations.hpp"
#include "player.hpp"


// -----------------------------------------------------------------------------
// load_animation_frames
// -----------------------------------------------------------------------------
void load_player_animation_frames(Animation &anim, PlayerAnimation id) {
  std::vector<int> frames;
  switch (id) {
    case PlayerAnimation::RunEast:
      frames = run_east();
      break;
    case PlayerAnimation::RunSouthEast:
      frames = run_southeast();
      break;
    case PlayerAnimation::RunSouth:
      frames = run_south();
      break;
    case PlayerAnimation::RunSouthWest:
      frames = run_southwest();
      break;
    case PlayerAnimation::RunWest:
      frames = run_west();
      break;
    case PlayerAnimation::RunNorthWest:
      frames = run_northwest();
      break;
    case PlayerAnimation::RunNorth:
      frames = run_north();
      break;
    case PlayerAnimation::RunNorthEast:
      frames = run_northeast();
      break;
  }

  // inits the anim with frame time and list of frames
  init(anim, player_frame_time, frames, player_frames);
}