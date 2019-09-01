#include "animation.hpp"
#include "data.hpp"

#include <iostream>
//
// init
//
void init(Animation &anim, int _frame_time, std::vector<int> &_frames,
          std::vector<sf::IntRect> &frame_rects) {
  anim.frame_time = _frame_time;
  anim.number_frames = _frames.size();
  assert(anim.number_frames <= MAX_ANIMATION_FRAMES);

  int i = 0;
  for (auto &frame : _frames) {
    anim.frames[i++] = frame_rects[frame];
  }
  anim.current_frame = 0;
}
//
// next_frame
//
void next_frame(Animation &anim) {
  if (++anim.current_frame == anim.number_frames) {
    if (anim.loop) {
      anim.current_frame = 0;
    } else {
      --anim.current_frame;
      anim.running = false;
    }
  }
}
//
// step
//
void step(Animation &anim) {
  if (!anim.running) return;
  if (++anim.timer == anim.frame_time) {
    anim.timer = 0;
    next_frame(anim);
  }
}
//
// frame
//
sf::IntRect frame(Animation &anim) { return anim.frames[anim.current_frame]; }
//
// update_animations
//
void update_animations() {
  for (auto &anim : live_animations) {
    step(anim.second);
    get_sprite(anim.first).setTextureRect(frame(anim.second));
  }
}
