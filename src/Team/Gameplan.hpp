#pragma once
#include "Ball/Ball.hpp"
#include "Pitch/Pitch.hpp"
namespace Senseless {
//
//
//
enum class DefensiveLineType { Deep, Normal, High };
enum class DefensivewidthType { Narrow, Normal, Wide };
//
//
//
class Gameplan {
 public:
  //
  //
  //
  Gameplan();
  //
  //
  //
  sf::Vector3f getDefensiveLine() const;
  //
  //
  //
  DefensiveLineType defensive_line_height = DefensiveLineType::Normal;
  DefensivewidthType defensive_width_type = DefensivewidthType::Narrow;

 private:
  //
  //
  //
  void updateDefensiveLine(const Pitch& in_pitch, const Ball& in_ball,
                           const Direction in_attacking_direction);
  //
  //
  //
  sf::Vector3f defensive_line;

 public:
  friend class Team;
};
}  // namespace Senseless
