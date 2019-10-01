#include "Compass.hpp"
#include "Vector.hpp"

#include <utility>

namespace Engine {
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
Compass::Compass(const Vector3 &vec) { fromVector(vec); }
//
//  toVector
//
Vector3 Compass::toVector() {
  Vector3 v;

  switch (direction) {
    case Direction::NORTH:
      v.x = 0;
      v.y = -1;
      break;

    case Direction::NORTH_EAST:
      v.x = 1;
      v.y = -1;
      break;

    case Direction::EAST:
      v.x = 1;
      v.y = 0;
      break;

    case Direction::SOUTH_EAST:
      v.x = 1;
      v.y = 1;
      break;

    case Direction::SOUTH:
      v.x = 0;
      v.y = 1;
      break;

    case Direction::SOUTH_WEST:
      v.x = -1;
      v.y = 1;
      break;

    case Direction::WEST:
      v.x = -1;
      v.y = 0;
      break;

    case Direction::NORTH_WEST:
      v.x = -1;
      v.y = -1;
      break;
  }

  return v;
}
//
//  fromVector
//
void Compass::fromVector(const Vector3 &v) {
  if (Math::equal(v.x, 0) && Math::less_than(v.y, 0))
    direction = Direction::NORTH;

  else if (Math::greater_than(v.x, 0) && Math::less_than(v.y, 0))
    direction = Direction::NORTH_EAST;

  else if (Math::greater_than(v.x, 0) && Math::equal(v.y, 0))
    direction = Direction::EAST;

  else if (Math::greater_than(v.x, 0) && Math::greater_than(v.y, 0))
    direction = Direction::SOUTH_EAST;

  else if (Math::equal(v.x, 0) && Math::greater_than(v.y, 0))
    direction = Direction::SOUTH;

  else if (Math::less_than(v.x, 0) && Math::greater_than(v.y, 0))
    direction = Direction::SOUTH_WEST;

  else if (Math::less_than(v.x, 0) && Math::equal(v.y, 0))
    direction = Direction::WEST;

  else if (Math::less_than(v.x, 0) && Math::less_than(v.y, 0))
    direction = Direction::NORTH_WEST;
}
}  // namespace Engine
