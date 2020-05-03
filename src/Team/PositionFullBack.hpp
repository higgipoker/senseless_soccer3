#pragma once
#include "PositionDefender.hpp"
namespace Senseless {
//
//
//
class PositionFullBack : public PositionDefender {
 public:
  //
  //
  //
  PositionFullBack(const Pitch &in_pitch, const Team &in_my_team, const Team &in_other_team)
      : PositionDefender(in_pitch, in_my_team, in_other_team) {}
  //
  //
  //
  void init() override;
  //
  //
  //
  Vector3 getPlayingPosition(const Ball &in_ball) override;
};

}  // namespace Senseless
