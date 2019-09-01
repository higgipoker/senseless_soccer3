#include "framerate.hpp"
//
//
//
void init(Framerate &framerate, float _target) {
  framerate.second_timer.restart();
  framerate.target_frame_time = _target;
}
//
//
//
void on_frame_started(Framerate &framerate) {
  framerate.gamestep_timer.restart();
  framerate.frame_start_time = static_cast<float>(
      framerate.gamestep_timer.getElapsedTime().asMilliseconds());
}
//
//
//
void on_frame_ended(Framerate &framerate) {
  float elapsed = framerate.second_timer.getElapsedTime().asMilliseconds();
  framerate.framecount++;
  if (elapsed >= 1000) {
    framerate.fps = framerate.framecount;
    framerate.framecount = 0;
    framerate.second_timer.restart();
  }
}
//
//
//
float time_left(Framerate &framerate) {
  float newnewtime = static_cast<float>(
      framerate.gamestep_timer.getElapsedTime().asMilliseconds());
  float frame_time = newnewtime - framerate.frame_start_time;
  float target = framerate.target_frame_time * 1000;
  return target - frame_time;
}
