#pragma once
#include "PositionForward.hpp"
//
//
//
class PositionCenterForward : public PositionForward {
    //
    //
    //
   public:
    //
    //
    //
    PositionCenterForward(const Pitch &in_pitch, const Team &in_my_team, const Team &in_other_team)
        : PositionForward(in_pitch, in_my_team, in_other_team) {
    }
    //
    //
    //
    void init() override;
    //
    //
    //
    Engine::Vector3 getPlayingPosition(const Ball &in_ball) override;
};
