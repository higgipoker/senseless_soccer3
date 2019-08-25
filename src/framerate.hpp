#pragma once
#include <SFML/System/Clock.hpp>

namespace Framerate {
/**
 * @brief a struct to manage constant frame rates
 */
struct Framerate {
  Framerate() { second_timer.restart(); }
  /**
   * @brief on_frame_started
   */
  inline void on_frame_started() {
    gamestep_timer.restart();
    frame_start_time =
        static_cast<float>(gamestep_timer.getElapsedTime().asMilliseconds());
  }

  /**
   * @brief on_frame_ended
   */
  inline void on_frame_ended() {
    float elapsed = second_timer.getElapsedTime().asMilliseconds();
    framecount++;
    if (elapsed >= 1000) {
      fps = framecount;
      framecount = 0;
      second_timer.restart();
      // std::cout << "frames: " << fps << std::endl;
    }
  }

  /**
   * @brief how long left to do the current frame
   * @param target_frame_time desired frame time
   * @return time left
   */
  inline float time_left(float target_frame_time) {
    float newnewtime =
        static_cast<float>(gamestep_timer.getElapsedTime().asMilliseconds());
    float frame_time = newnewtime - frame_start_time;
    float target = target_frame_time * 1000;
    return target - frame_time;
  }
  sf::Clock gamestep_timer;
  sf::Clock second_timer;
  float frame_start_time = 0;
  float framecount = 0;
  float fps = 0;
};
}  // namespace Framerate
