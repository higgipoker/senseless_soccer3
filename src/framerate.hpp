#pragma once
#include <SFML/System/Clock.hpp>

namespace Framerate {
/**
 * @brief a struct to manage constant frame rates
 */
struct Framerate {
  sf::Clock gamestep_timer;
  sf::Clock second_timer;
  float frame_start_time = 0;
  float framecount = 0;
  float fps = 0;
  float target_frame_time = 0;
};

/**
 * @brief init
 * @param framerate
 */
inline void init(Framerate &framerate, float _target) {
  framerate.second_timer.restart();
  framerate.target_frame_time = _target;
}

/**
 * @brief on_frame_started
 */
inline void on_frame_started(Framerate &framerate) {
  framerate.gamestep_timer.restart();
  framerate.frame_start_time = static_cast<float>(
      framerate.gamestep_timer.getElapsedTime().asMilliseconds());
}

/**
 * @brief on_frame_ended
 */
inline void on_frame_ended(Framerate &framerate) {
  float elapsed = framerate.second_timer.getElapsedTime().asMilliseconds();
  framerate.framecount++;
  if (elapsed >= 1000) {
    framerate.fps = framerate.framecount;
    framerate.framecount = 0;
    framerate.second_timer.restart();
  }
}

/**
 * @brief how long left to do the current frame
 * @param target_frame_time desired frame time
 * @return time left
 */
inline float time_left(Framerate &framerate) {
  float newnewtime = static_cast<float>(
      framerate.gamestep_timer.getElapsedTime().asMilliseconds());
  float frame_time = newnewtime - framerate.frame_start_time;
  float target = framerate.target_frame_time * 1000;
  return target - frame_time;
}
}  // namespace Framerate
