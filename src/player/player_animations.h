#pragma once

#include <gamelib3/physics/movable.hpp>

#include <vector>

namespace senseless_soccer3 {

const float anim_speed = 0.5 * 10000;

// -----------------------------------------------------------------------------
// standing animations
// -----------------------------------------------------------------------------
static std::vector<int> stand_east() { return std::vector<int>{1}; }
static std::vector<int> stand_southeast() { return std::vector<int>{4}; }
static std::vector<int> stand_south() { return std::vector<int>{7}; }
static std::vector<int> stand_southwest() { return std::vector<int>{10}; }
static std::vector<int> stand_west() { return std::vector<int>{13}; }
static std::vector<int> stand_northwest() { return std::vector<int>{16}; }
static std::vector<int> stand_north() { return std::vector<int>{19}; }
static std::vector<int> stand_northeast() { return std::vector<int>{22}; }

// -----------------------------------------------------------------------------
// running animations
// -----------------------------------------------------------------------------
static std::vector<int> run_east() { return std::vector<int>{0, 1}; }
static std::vector<int> run_southeast() { return std::vector<int>{3, 5}; }
static std::vector<int> run_south() { return std::vector<int>{6, 8}; }
static std::vector<int> run_southwest() { return std::vector<int>{9, 11}; }
static std::vector<int> run_west() { return std::vector<int>{12, 13}; }
static std::vector<int> run_northwest() { return std::vector<int>{15, 17}; }
static std::vector<int> run_north() { return std::vector<int>{18, 20}; }
static std::vector<int> run_northeast() { return std::vector<int>{21, 23}; }

// -----------------------------------------------------------------------------
// sliding animations
// -----------------------------------------------------------------------------
static std::vector<int> slide_east() {
  std::vector<int> v;
  v.push_back(24);
  v.push_back(25);
  for (int i = 0; i < 2; ++i) v.push_back(26);
  return v;
}
static std::vector<int> slide_southeast() {
  std::vector<int> v{27, 28};
  for (int i = 0; i < 2; ++i) v.push_back(29);
  return v;
}
static std::vector<int> slide_south() {
  std::vector<int> v{30, 31};
  for (int i = 0; i < 2; ++i) v.push_back(32);
  return v;
}
static std::vector<int> slide_southwest() {
  std::vector<int> v{33, 34};
  for (int i = 0; i < 2; ++i) v.push_back(35);
  return v;
}
static std::vector<int> slide_west() {
  std::vector<int> v{36, 37};
  for (int i = 0; i < 2; ++i) v.push_back(38);
  return v;
}
static std::vector<int> slide_northwest() {
  std::vector<int> v{39, 40};
  for (int i = 0; i < 2; ++i) v.push_back(41);
  return v;
}

static std::vector<int> slide_north() {
  std::vector<int> v{42, 43};
  for (int i = 0; i < 2; ++i) v.push_back(44);
  return v;
}
static std::vector<int> slide_northeast() {
  std::vector<int> v{45, 46};
  for (int i = 0; i < 2; ++i) v.push_back(47);
  return v;
}

/**
 * @brief populate_animations
 * @param m
 */
void populate_animations(gamelib3::Movable &m) {
  m.AddAnimation("stand_east", anim_speed, true, stand_east());
  m.AddAnimation("stand_southeast", anim_speed, true, stand_southeast());
  m.AddAnimation("stand_south", anim_speed, true, stand_south());
  m.AddAnimation("stand_southwest", anim_speed, true, stand_southwest());
  m.AddAnimation("stand_west", anim_speed, true, stand_west());
  m.AddAnimation("stand_northwest", anim_speed, true, stand_northwest());
  m.AddAnimation("stand_north", anim_speed, true, stand_north());
  m.AddAnimation("stand_northeast", anim_speed, true, stand_northeast());

  m.AddAnimation("run_east", anim_speed, true, run_east());
  m.AddAnimation("run_southeast", anim_speed, true, run_southeast());
  m.AddAnimation("run_south", anim_speed, true, run_south());
  m.AddAnimation("run_southwest", anim_speed, true, run_southwest());
  m.AddAnimation("run_west", anim_speed, true, run_west());
  m.AddAnimation("run_northwest", anim_speed, true, run_northwest());
  m.AddAnimation("run_north", anim_speed, true, run_north());
  m.AddAnimation("run_northeast", anim_speed, true, run_northeast());

  m.AddAnimation("slide_east", anim_speed, false, slide_east());
  m.AddAnimation("slide_southeast", anim_speed, false, slide_southeast());
  m.AddAnimation("slide_south", anim_speed, false, slide_south());
  m.AddAnimation("slide_southwest", anim_speed, false, slide_southwest());
  m.AddAnimation("slide_west", anim_speed, false, slide_west());
  m.AddAnimation("slide_northwest", anim_speed, false, slide_northwest());
  m.AddAnimation("slide_north", anim_speed, false, slide_north());
  m.AddAnimation("slide_northeast", anim_speed, false, slide_northeast());
}

}  // namespace senseless_soccer3
