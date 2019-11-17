#pragma once
#include "PositionDefender.hpp"
//
//
//
class PositionFullBack : public PositionDefender {
   public:
    //
    //
    //
    PositionFullBack(const Pitch &in_pitch) : PositionDefender(in_pitch) {
    }
    //
    //
    //
    void init() override;
    //
    //
    //
    Engine::Vector3 getPlayingPosition(const Situation in_situation, const Team &in_my_team, const Team &in_other_team, const Ball &in_ball) override;
};
