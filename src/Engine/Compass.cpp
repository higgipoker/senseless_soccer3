#include "Compass.hpp"
#include "Vector.hpp"

#include <utility>

namespace Senseless {
//
//  constructor
//
Compass::Compass() = default;
//
//  constructor
//
Compass ::Compass(Direction dir) : direction(dir) {}
//
//  constructor
//
Compass::Compass(const sf::Vector3f &vec) { fromSfVector(vec); }

sf::Vector3f Compass::toSfVector() {
  sf::Vector3f v;

  switch (direction) {
    case Direction::North:
      v.x = 0;
      v.y = -1;
      break;

    case Direction::NorthEast:
      v.x = 1;
      v.y = -1;
      break;

    case Direction::East:
      v.x = 1;
      v.y = 0;
      break;

    case Direction::SouthEast:
      v.x = 1;
      v.y = 1;
      break;

    case Direction::South:
      v.x = 0;
      v.y = 1;
      break;

    case Direction::SouthWest:
      v.x = -1;
      v.y = 1;
      break;

    case Direction::West:
      v.x = -1;
      v.y = 0;
      break;

    case Direction::NorthWest:
      v.x = -1;
      v.y = -1;
      break;
  }

  return v;
}
//
//
//
sf::Vector3f Compass::toSfVector(const Direction in_direction){
    Compass c{in_direction};
    return c.toSfVector();
}
void Compass::fromSfVector(const sf::Vector3f &v) {
  if (Math::equal(v.x, 0) && Math::less_than(v.y, 0))
    direction = Direction::North;

  else if (Math::greater_than(v.x, 0) && Math::less_than(v.y, 0))
    direction = Direction::NorthEast;

  else if (Math::greater_than(v.x, 0) && Math::equal(v.y, 0))
    direction = Direction::East;

  else if (Math::greater_than(v.x, 0) && Math::greater_than(v.y, 0))
    direction = Direction::SouthEast;

  else if (Math::equal(v.x, 0) && Math::greater_than(v.y, 0))
    direction = Direction::South;

  else if (Math::less_than(v.x, 0) && Math::greater_than(v.y, 0))
    direction = Direction::SouthWest;

  else if (Math::less_than(v.x, 0) && Math::equal(v.y, 0))
    direction = Direction::West;

  else if (Math::less_than(v.x, 0) && Math::less_than(v.y, 0))
    direction = Direction::NorthWest;
}
//
//
//
Compass Compass::getRandomDirection() {
  return {(static_cast<Direction>(rand() % 7))};
}
}  // namespace Senseless
