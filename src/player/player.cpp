#include "player.hpp"
using namespace gamelib3;
namespace senseless_soccer3 {

std::map<Direction, std::string> Player::standmap;
std::map<Direction, std::string> Player::runmap;
std::map<Direction, std::string> Player::slidemap;

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

Player::Player() { width = 32; }

void Player::Init() {
  // standing animations
  standmap.insert(std::make_pair(Direction::SOUTH_EAST, "stand_southeast"));
  standmap.insert(std::make_pair(Direction::SOUTH, "stand_south"));
  standmap.insert(std::make_pair(Direction::SOUTH_WEST, "stand_southwest"));
  standmap.insert(std::make_pair(Direction::WEST, "stand_west"));
  standmap.insert(std::make_pair(Direction::NORTH_WEST, "stand_northwest"));
  standmap.insert(std::make_pair(Direction::NORTH, "stand_north"));
  standmap.insert(std::make_pair(Direction::NORTH_EAST, "stand_northeast"));
  standmap.insert(std::make_pair(Direction::EAST, "stand_east"));

  // running animations
  runmap.insert(std::make_pair(Direction::SOUTH_EAST, "run_southeast"));
  runmap.insert(std::make_pair(Direction::SOUTH, "run_south"));
  runmap.insert(std::make_pair(Direction::SOUTH_WEST, "run_southwest"));
  runmap.insert(std::make_pair(Direction::WEST, "run_west"));
  runmap.insert(std::make_pair(Direction::NORTH_WEST, "run_northwest"));
  runmap.insert(std::make_pair(Direction::NORTH, "run_north"));
  runmap.insert(std::make_pair(Direction::NORTH_EAST, "run_northeast"));
  runmap.insert(std::make_pair(Direction::EAST, "run_east"));

  // sliding animations
  slidemap.insert(std::make_pair(Direction::SOUTH_EAST, "slide_southeast"));
  slidemap.insert(std::make_pair(Direction::SOUTH, "slide_south"));
  slidemap.insert(std::make_pair(Direction::SOUTH_WEST, "slide_southwest"));
  slidemap.insert(std::make_pair(Direction::WEST, "slide_west"));
  slidemap.insert(std::make_pair(Direction::NORTH_WEST, "slide_northwest"));
  slidemap.insert(std::make_pair(Direction::NORTH, "slide_north"));
  slidemap.insert(std::make_pair(Direction::NORTH_EAST, "slide_northeast"));
  slidemap.insert(std::make_pair(Direction::EAST, "slide_east"));

  AddAnimation("stand_east", anim_speed, true, stand_east());
  AddAnimation("stand_southeast", anim_speed, true, stand_southeast());
  AddAnimation("stand_south", anim_speed, true, stand_south());
  AddAnimation("stand_southwest", anim_speed, true, stand_southwest());
  AddAnimation("stand_west", anim_speed, true, stand_west());
  AddAnimation("stand_northwest", anim_speed, true, stand_northwest());
  AddAnimation("stand_north", anim_speed, true, stand_north());
  AddAnimation("stand_northeast", anim_speed, true, stand_northeast());

  AddAnimation("run_east", anim_speed, true, run_east());
  AddAnimation("run_southeast", anim_speed, true, run_southeast());
  AddAnimation("run_south", anim_speed, true, run_south());
  AddAnimation("run_southwest", anim_speed, true, run_southwest());
  AddAnimation("run_west", anim_speed, true, run_west());
  AddAnimation("run_northwest", anim_speed, true, run_northwest());
  AddAnimation("run_north", anim_speed, true, run_north());
  AddAnimation("run_northeast", anim_speed, true, run_northeast());

  AddAnimation("slide_east", anim_speed, false, slide_east());
  AddAnimation("slide_southeast", anim_speed, false, slide_southeast());
  AddAnimation("slide_south", anim_speed, false, slide_south());
  AddAnimation("slide_southwest", anim_speed, false, slide_southwest());
  AddAnimation("slide_west", anim_speed, false, slide_west());
  AddAnimation("slide_northwest", anim_speed, false, slide_northwest());
  AddAnimation("slide_north", anim_speed, false, slide_north());
  AddAnimation("slide_northeast", anim_speed, false, slide_northeast());
}
}  // namespace senseless_soccer3
