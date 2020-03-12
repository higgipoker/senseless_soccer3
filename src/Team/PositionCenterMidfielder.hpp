#pragma once
#include "PositionMidfielder.hpp"
//
//
//
class PositionCenterMidfielder : public PositionMidfielder {
   public:
    //
    //
    //
    PositionCenterMidfielder(const Pitch &in_pitch, const Team &in_my_team, const Team &in_other_team)
        : PositionMidfielder(in_pitch, in_my_team, in_other_team) {
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
