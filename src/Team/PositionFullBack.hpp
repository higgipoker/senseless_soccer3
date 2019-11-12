#pragma once
#include "PositionDefender.hpp"
//
//
//
class PositionFullBack : public PositionDefender {
   public:
    Engine::Vector3 getTargetPosition(const Pitch &in_pitch, const Team &in_my_team, const Team &in_other_team,
                                      const Ball &in_ball) override;
};
