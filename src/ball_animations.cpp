#include "ball_animations.hpp"
#include "ball.hpp"

Anims roll_left() { return Anims{0, 1, 2, 3, 4, 5, 6}; }
//
//
//
void load_ball_animation_frames(Animation &anim, BallAnimation id) {
  std::vector<int> frames;
  switch (id) {
    case BallAnimation::RollLeft:
      frames = roll_left();
      break;
  }

  // inits the anim with frame time and list of frames
  init(anim, ball_frame_time, frames, ball_frames);
}
