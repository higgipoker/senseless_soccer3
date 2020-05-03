#pragma once
#include "PlayingPosition.hpp"
namespace Senseless {
//
//
//
class PositionDefender : public PlayingPosition {
 public:
  //
  //
  //
  PositionDefender(const Pitch &in_pitch, const Team &in_my_team, const Team &in_other_team)
      : PlayingPosition(in_pitch, in_my_team, in_other_team) {}
};
}  // namespace Senseless
