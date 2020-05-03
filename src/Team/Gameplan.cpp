#include "Gameplan.hpp"

#include <algorithm>
//
namespace Senseless {
//
//
//
Gameplan::Gameplan() {}
//
//
//
void Gameplan::updateDefensiveLine(const Pitch &in_pitch, const Ball &in_ball,
                                   const Direction in_attacking_direction) {
  Vector3 ball = in_pitch.toPitchSpace(in_ball.movable.position);

  const float min = 0;                                                // goal line
  const float max = in_pitch.getDimensions().bounds.getSize().y / 2;  // half way line

  switch (defensive_line_height) {
    case DefensiveLineType::Deep:
      defensive_line.y = std::clamp(ball.y * 0.4F, min, max);
      break;
    case DefensiveLineType::Normal:
      defensive_line.y = std::clamp(ball.y * 0.6F, min, max);
      break;
    case DefensiveLineType::High:
      defensive_line.y = std::clamp(ball.y * 0.8F, min, max);
      break;
  }
}
//
//
//
Vector3 Gameplan::getDefensiveLine() const { return defensive_line; }
}  // namespace Senseless
