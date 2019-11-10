#include "PositionCenterBack.hpp"
//
#include "Team.hpp"
//
//
//
Engine::Vector3 PositionCenterBack::getTargetPosition(const Pitch &in_pitch, const Team &in_my_team,
                                                      const Team &in_other_team, const Ball &in_ball) {
    Engine::Vector3 target_position (300, in_my_team.gameplan.getDefensiveLine(in_pitch, in_ball, in_my_team.getAttackingGoal()));

    return target_position;
}
