#pragma once
#include "PositionDefender.hpp"
//
//
//
class PositionCenterBack : public PositionDefender {
   public:
    /**
     * @brief PositionCenterBack
     * @param in_pitch
     * @param in_my_team
     * @param in_other_team
     */
    PositionCenterBack(const Pitch &in_pitch, const Team &in_my_team, const Team &in_other_team)
        : PositionDefender(in_pitch, in_my_team, in_other_team) {
    }
    /**
     * @brief init
     */
    void init() override;
    /**
     * @brief getPlayingPosition
     * @param in_ball
     * @return
     */
    Engine::Vector3 getPlayingPosition(const Ball &in_ball) override;
};
