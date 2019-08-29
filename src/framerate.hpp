#pragma once
#include <SFML/System/Clock.hpp>

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
void init(Framerate &framerate, float _target) ;
/**
 * @brief on_frame_started
 */
void on_frame_started(Framerate &framerate) ;
/**
 * @brief on_frame_ended
 */
void on_frame_ended(Framerate &framerate) ;
/**
 * @brief how long left to do the current frame
 * @param target_frame_time desired frame time
 * @return time left
 */
float time_left(Framerate &framerate);
