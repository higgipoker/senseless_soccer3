#include "SpriteAnimation.hpp"
namespace Engine {
//
//
//
SpriteAnimation::SpriteAnimation(const int in_speed,
                                 const std::vector<int>& in_frames,
                                 bool in_loop) {
  frame_speed = in_speed;
  frames = in_frames;
  loop = in_loop;
  current_frame = frames.begin();
}
//
//
//
SpriteAnimation::SpriteAnimation(std::initializer_list<int> in_args) {
  for (auto& arg : in_args) {
    frames.push_back(arg);
  }
  // the first arg was the anim speed
  frame_speed = frames.front();
  frames.erase(frames.begin());
  current_frame = frames.begin();
}
//
//
//
void SpriteAnimation::step() {
  if (++count_frames > frame_speed) {
    count_frames = 0;
    if (++current_frame == frames.end()) {
      if (loop) {
        current_frame = frames.begin();
      } else {
        finito = true;
      }
    }
  }
}
//
//
//
bool SpriteAnimation::finished() { return finito; }
//
//
//
void SpriteAnimation::setLoopable(bool in_yesorno) { loop = in_yesorno; }
//
//
//
int SpriteAnimation::currentFrame(){
  return  *current_frame;
}
}  // namespace Engine
