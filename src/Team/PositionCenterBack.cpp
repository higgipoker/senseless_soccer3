#include "PositionCenterBack.hpp"
//
#include "Team.hpp"
//
using namespace Engine;
//
//
//
void PositionCenterBack::init() {
    {  // kick off positions
        Vector3 def{0, pitch.getPointOfInterest(PitchPointsOfInterest::CenterSpot).y * 0.35F};
        Vector3 att{0, pitch.getPointOfInterest(PitchPointsOfInterest::CenterSpot).y * 0.55F};
        if (modifier_mask & modifier_left) {
            def.x = att.x = pitch.getPointOfInterest(PitchPointsOfInterest::CentercircleWest).x;

        } else if (modifier_mask & modifier_right) {
            def.x = att.x = pitch.getPointOfInterest(PitchPointsOfInterest::CentercircleEast).x;
        }
        set_piece_positions_defending[Situation::KickOff] = {{def}, {def}};
        set_piece_positions_attacking[Situation::KickOff] = {{att}, {att}};
    }

    {  // goal kick positions
        Vector3 def{0, pitch.getPointOfInterest(PitchPointsOfInterest::Eighteen).y};
        Vector3 att{0, pitch.getPointOfInterest(PitchPointsOfInterest::Eighteen).y};
        if (modifier_mask & modifier_left) {
            def.x = att.x = pitch.getPointOfInterest(PitchPointsOfInterest::CenterSpot).x - 100;

        } else if (modifier_mask & modifier_right) {
            def.x = att.x = pitch.getPointOfInterest(PitchPointsOfInterest::CenterSpot).x + 100;
        }
        set_piece_positions_defending[Situation::GoalKick] = {{def}, {def}};
        set_piece_positions_attacking[Situation::GoalKick] = {{att}, {att}};
    }
}
//
//
//
Engine::Vector3 PositionCenterBack::getPlayingPosition(const Situation in_situation, const Ball &in_ball) {
    Vector3 ball = pitch.toPitchSpace(in_ball.movable.position);
    // rotate perception of ball if attacking towards south
    if (my_team.getAttackingGoal() == Direction::South) {
        ball.rotate(180, pitch.getDimensions().bounds.getSize().x / 2, pitch.getDimensions().bounds.getSize().y / 2);
    }

    float middle = pitch.getDimensions().bounds.getSize().x / 2;
    float ball_to_middle = ball.x - middle;
    float out_x = 0;
    switch (my_team.gameplan.defensive_width_type) {
        case DefensivewidthType::Narrow:
            out_x = middle + ball_to_middle * 0.3F;
            break;
        case DefensivewidthType::Normal:
            out_x = middle + ball_to_middle * 0.6F;
            break;
        case DefensivewidthType::Wide:
            out_x = middle + ball_to_middle * 1.0F;
            break;
    }

    // constrain
    float min = 0;
    float max = 0;
    float constraint_width = 0;
    if (modifier_mask & modifier_left) {
        constraint_width = pitch.getDimensions().bounds.getSize().x * 0.2F;
        min = middle - constraint_width;
        max = middle - constraint_width / 3;
    }
    if (modifier_mask & modifier_right) {
        constraint_width = pitch.getDimensions().bounds.getSize().x * 0.2F;
        min = middle + constraint_width / 3;
        max = middle + constraint_width;
    }
    out_x = std::clamp(out_x, min, max);
    Vector3 result{out_x, my_team.gameplan.getDefensiveLine().y};

    // rotate for other side?
    if (my_team.getAttackingGoal() == Direction::South) {
        // since the team y defensive line has already been calced, only rotate x here
        Vector3 tmp{result.x, 0};
        tmp.rotate(180, middle, 0);
        result.x = tmp.x;
    }

    return result;
}
