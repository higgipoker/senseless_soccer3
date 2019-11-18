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
Engine::Vector3 PlayingPosition::getTargetPosition(const Situation in_situation, const Ball &in_ball,
                                                   const Direction in_pitch_side) {
    Vector3 result;
    switch (in_situation) {
        case Situation::Playing:
            result = getPlayingPosition(in_situation, in_ball);
            break;
        case Situation::KickOff:
        case Situation::GoalKick:
        case Situation::Corner:
        case Situation::FreeKick:
        case Situation::ThrowIn:
            result = getSetPiecePosition(in_situation, in_ball, in_pitch_side);
            // rotate for other side?
            if (my_team.getAttackingGoal() == Direction::South) {
                // since the team y defensive line has already been calced, only rotate x here
                Vector3 tmp{result.x, 0};
                tmp.rotate(180, pitch.getPointOfInterest(PitchPointsOfInterest::CenterSpot).x, 0);
                result.x = tmp.x;
            }
            break;
    }
    return pitch.toScreenSpace(result);
}
//
//
//
Engine::Vector3 PlayingPosition::getSetPiecePosition(const Situation in_situation, const Ball &in_ball,
                                                     const Direction in_pitch_side) {
    Engine::Vector3 result;
    switch (my_team.getAttackingState()) {
        case AttackingState::Defending:
            if (in_pitch_side == Direction::West) {
                result = set_piece_positions_defending[in_situation].first;
            } else {
                result = set_piece_positions_defending[in_situation].second;
            }
            break;
        case AttackingState::Attacking:
            if (in_pitch_side == Direction::West) {
                result = set_piece_positions_attacking[in_situation].first;
            } else {
                result = set_piece_positions_attacking[in_situation].second;
            }
            break;
    }
    // rotate south->north?
    if (my_team.getAttackingGoal() == Direction::South) {
        Vector3 tmp{0, result.y};
        tmp.rotate(180, 0, pitch.getDimensions().halfway_line.getPosition().y);
        result.y = tmp.y;
    }
    return result;
}
