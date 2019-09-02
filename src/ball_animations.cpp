#include "ball_animations.hpp"
#include "ball.hpp"
//
//
//
void init_ball_animations() {
  ball_roll_animations.clear();
  Animation anim;
  // roll animations
  init_animation(anim, ball_frame_time, roll_left, ball_frames);
  ball_roll_animations[Direction::WEST] = anim;
}
