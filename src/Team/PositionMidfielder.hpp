#pragma once
#include "PlayingPosition.hpp"
//
//
//
class PositionMidfielder : public PlayingPosition {
   public:
    //
    //
    //
    PositionMidfielder(const Pitch &in_pitch, const Team &in_my_team, const Team &in_other_team)
        : PlayingPosition(in_pitch, in_my_team, in_other_team) {
    }
};
