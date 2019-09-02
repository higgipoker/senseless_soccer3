#include "player_animations.hpp"
#include "player.hpp"
//
//
//
void init_player_animations() {
  player_stand_animations.clear();
  Animation anim;

  // standing animations
  init_animation(anim, player_frame_time, stand_north, player_frames);
  player_stand_animations[Direction::NORTH] = anim;

  init_animation(anim, player_frame_time, stand_northeast, player_frames);
  player_stand_animations[Direction::NORTH_EAST] = anim;

  init_animation(anim, player_frame_time, stand_east, player_frames);
  player_stand_animations[Direction::EAST] = anim;

  init_animation(anim, player_frame_time, stand_southeast, player_frames);
  player_stand_animations[Direction::SOUTH_EAST] = anim;

  init_animation(anim, player_frame_time, stand_south, player_frames);
  player_stand_animations[Direction::SOUTH] = anim;

  init_animation(anim, player_frame_time, stand_southwest, player_frames);
  player_stand_animations[Direction::SOUTH_WEST] = anim;

  init_animation(anim, player_frame_time, stand_west, player_frames);
  player_stand_animations[Direction::WEST] = anim;

  init_animation(anim, player_frame_time, stand_northwest, player_frames);
  player_stand_animations[Direction::NORTH_WEST] = anim;
  //
  // running animations
  //
  player_run_animations.clear();
  init_animation(anim, player_frame_time, run_north, player_frames);
  player_run_animations[Direction::NORTH] = anim;

  init_animation(anim, player_frame_time, run_northeast, player_frames);
  player_run_animations[Direction::NORTH_EAST] = anim;

  init_animation(anim, player_frame_time, run_east, player_frames);
  player_run_animations[Direction::EAST] = anim;

  init_animation(anim, player_frame_time, run_southeast, player_frames);
  player_run_animations[Direction::SOUTH_EAST] = anim;

  init_animation(anim, player_frame_time, run_south, player_frames);
  player_run_animations[Direction::SOUTH] = anim;

  init_animation(anim, player_frame_time, run_southwest, player_frames);
  player_run_animations[Direction::SOUTH_WEST] = anim;

  init_animation(anim, player_frame_time, run_west, player_frames);
  player_run_animations[Direction::WEST] = anim;

  init_animation(anim, player_frame_time, run_northwest, player_frames);
  player_run_animations[Direction::NORTH_WEST] = anim;
}
