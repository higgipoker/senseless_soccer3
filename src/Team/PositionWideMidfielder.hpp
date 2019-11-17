#pragma once
#include "PositionMidfielder.hpp"
//
//
//
class PositionWideMidfielder : public PositionMidfielder {
   public:
    //
    //
    //
    PositionWideMidfielder(const Pitch &in_pitch) : PositionMidfielder(in_pitch) {
    }
    //
    //
    //
    void init() override;
    //
    //
    //
    Engine::Vector3 getTargetPosition(const Situation in_situation, const Team &in_my_team, const Team &in_other_team, const Ball &in_ball) override;
};
