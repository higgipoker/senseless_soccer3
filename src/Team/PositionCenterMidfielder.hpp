#pragma once
#include "PositionMidfielder.hpp"
namespace Senseless {
//
//
//
class PositionCenterMidfielder : public PositionMidfielder {
 public:
  //
  //
  //
  PositionCenterMidfielder(const Pitch &in_pitch, const Team &in_my_team, const Team &in_other_team)
      : PositionMidfielder(in_pitch, in_my_team, in_other_team) {}
  //
  //
  //
  void init() override;
  //
  //
  //
  sf::Vector3f getPlayingPosition(const Ball &in_ball) override;
};
}  // namespace Senseless
