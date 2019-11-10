#pragma once
#include <map>
#include <string>

namespace Engine {
//
//
//
enum class Direction : int { North = 0, NorthEast, East, SouthEast, South, SouthWest, West, NorthWest };
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
    Direction direction = Direction::North;
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
    inline std::string print() {
        return direction_to_string[direction];
    }
};
}  // namespace Engine
