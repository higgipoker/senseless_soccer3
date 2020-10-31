#pragma once

#include <SFML/System/Vector3.hpp>

#include <map>
#include <string>

namespace Senseless {
//
//
//
enum class Direction : int {
  North = 0,
  NorthEast,
  East,
  SouthEast,
  South,
  SouthWest,
  West,
  NorthWest
};
//
//
//
static std::map<Direction, std::string> direction_to_string = {
    std::make_pair(Direction::North, "North"), std::make_pair(Direction::NorthEast, "NorthEast"),
    std::make_pair(Direction::East, "East"),   std::make_pair(Direction::SouthEast, "SouthEast"),
    std::make_pair(Direction::South, "South"), std::make_pair(Direction::SouthWest, "SouthWest"),
    std::make_pair(Direction::West, "West"),   std::make_pair(Direction::NorthWest, "NorthWest")};
//
//
//
class Compass {
 public:
  Compass();
  Compass(Direction dir);
  Compass(const sf::Vector3f &vec);
  sf::Vector3f toSfVector();
  void fromSfVector(const sf::Vector3f &v);  
  static sf::Vector3f toSfVector(const Direction in_direction);
  Direction direction = Direction::North;
  static Compass getRandomDirection();
  inline std::string print() { return direction_to_string[direction]; }
  inline bool operator==(const Compass &rhs) { return direction == rhs.direction; }
  inline bool operator!=(const Compass &rhs) { return direction != rhs.direction; }  
};
}  // namespace Senseless
