#pragma once

#include <map>

namespace Engine {
//
//
//
enum class Direction : int{
  NORTH = 0,
  NORTH_EAST,
  EAST,
  SOUTH_EAST,
  SOUTH,
  SOUTH_WEST,
  WEST,
  NORTH_WEST
};
//
//
//
static std::map<Direction, std::string> direction_to_string = {
    std::make_pair(Direction::NORTH, "NORTH"),
    std::make_pair(Direction::NORTH_EAST, "NORTH_EAST"),
    std::make_pair(Direction::EAST, "EAST"),
    std::make_pair(Direction::SOUTH_EAST, "SOUTH_EAST"),
    std::make_pair(Direction::SOUTH, "SOUTH"),
    std::make_pair(Direction::SOUTH_WEST, "SOUTH_WEST"),
    std::make_pair(Direction::WEST, "WEST"),
    std::make_pair(Direction::NORTH_WEST, "NORTH_WEST")};
//
//
//
class Vector3;
//
//
//
class Compass {
 public:
  //
  //
  //
  Compass();
  //
  //
  //
  Compass(Direction dir);
  //
  //
  //
  Compass(const Vector3 &vec);
  //
  //
  //
  Vector3 toVector();
  //
  //
  //
  void fromVector(const Vector3 &v);
  //
  //
  //
  Direction direction = Direction::NORTH;
  //
  //
  //
  inline bool operator==(const Compass &rhs) {
    return direction == rhs.direction;
  }
  //
  //
  //
  inline bool operator!=(const Compass &rhs) {
    return direction != rhs.direction;
  }
  //
  //
  //
  static Compass getRandomDirection();
  //
  //
  //
  inline std::string print() { return direction_to_string[direction]; }
};
}  // namespace Engine
