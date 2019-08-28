#pragma once
#include <array>
#include <cassert>
#include <vector>

static const int MAX_ANIMATION_FRAMES = 50;

/**
 * @brief The Animation struct
 */
struct Animation {
  int frame_time = 0;
  int timer = 0;
  int number_frames = 0;
  int current_frame = 0;
  bool loop = true;
  bool running = true;
  std::array<int, MAX_ANIMATION_FRAMES> frames;
};

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
inline void init(Animation &anim, int _frame_time, std::vector<int> &_frames) {
  anim.frame_time = _frame_time;
  anim.number_frames = _frames.size();
  assert(anim.number_frames <= MAX_ANIMATION_FRAMES);

  int i = 0;
  for (auto &frame : _frames) {
    anim.frames[i++] = frame;
  }
  anim.current_frame = 0;
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
inline void next_frame(Animation &anim) {
  if (++anim.current_frame == anim.number_frames) {
    if (anim.loop) {
      anim.current_frame = 0;
    } else {
      --anim.current_frame;
      anim.running = false;
    }
  }
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
inline void step(Animation &anim) {
  if (!anim.running) return;
  if (++anim.timer == anim.frame_time) {
    anim.timer = 0;
    next_frame(anim);
  }
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
inline int frame(Animation &anim) { return anim.frames[anim.current_frame]; }
