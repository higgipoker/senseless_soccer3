#include "PlayingPosition.hpp"
//
#include "Team.hpp"
//
using namespace Engine;
//
int PlayingPosition::instances = 0;
//
//
//
void PlayingPosition::applyModifier(const PositionModifier in_mod) {
    switch (in_mod) {
        case PositionModifier::Center:
            modifier_mask |= modifier_center;
            break;
        case PositionModifier::Left:
            modifier_mask |= modifier_left;
            break;
        case PositionModifier::Right:
            modifier_mask |= modifier_right;
            break;
        case PositionModifier::Attacking:
            modifier_mask |= modifier_attacking;
            break;
        case PositionModifier::Defensive:
            modifier_mask |= modifier_defensive;
            break;
    }
    init();
}
//
//
//
Engine::Vector3 PlayingPosition::getTargetPosition(const Situation in_situation, const Team &in_my_team,
                                                   const Team &in_other_team, const Ball &in_ball) {
    Vector3 result;
    switch (in_situation) {
        case Situation::Playing:
            result = getPlayingPosition(in_situation, in_my_team, in_other_team, in_ball);
            break;
        case Situation::KickOff:
            result = getSetPiecePosition(in_situation, in_my_team, in_other_team, in_ball);
            break;
        case Situation::GoalKick:
            break;
        case Situation::Corner:
            break;
        case Situation::FreeKick:
            break;
        case Situation::ThrowIn:
            break;
    }
    return pitch.toScreenSpace(result);
}
//
//
//
Engine::Vector3 PlayingPosition::getSetPiecePosition(const Situation in_situation, const Team &in_my_team,
                                                     const Team &in_other_team, const Ball &in_ball) {
    Engine::Vector3 result;
    switch (in_situation) {
        case Situation::KickOff: {
            result = set_piece_positions[Situation::KickOff].first;
            // rotate south->north?
            if (in_my_team.getAttackingGoal() == Direction::South) {
                Vector3 tmp{0, result.y};
                tmp.rotate(180, 0, pitch.getDimensions().halfway_line.getPosition().y);
                result.y = tmp.y;
            }
        } break;
        case Situation::GoalKick:
            break;
        case Situation::Corner:
            break;
        case Situation::FreeKick:
            break;
        case Situation::ThrowIn:
            break;
        case Situation::Playing:
            break;
    }
    return result;
}
