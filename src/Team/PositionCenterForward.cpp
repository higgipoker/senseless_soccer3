#include "PositionCenterForward.hpp"
//
#include "Team.hpp"
//
using namespace Engine;
//
//
//
void PositionCenterForward::init() {
    {  // kick off positions
        // ball is in center so out ball east and west are the same
        Vector3 def{0, pitch.getPointOfInterest(PitchPointsOfInterest::CenterSpot).y};
        Vector3 att{0, pitch.getPointOfInterest(PitchPointsOfInterest::CenterSpot).y};
        if (modifier_mask & modifier_left) {
            def.x = pitch.getPointOfInterest(PitchPointsOfInterest::CentercircleWest).x;
            att.x = pitch.getPointOfInterest(PitchPointsOfInterest::CenterSpot).x - 20;

        } else if (modifier_mask & modifier_right) {
            def.x = pitch.getPointOfInterest(PitchPointsOfInterest::CentercircleEast).x;
            att.x = pitch.getPointOfInterest(PitchPointsOfInterest::CenterSpot).x + 20;
        }
        set_piece_positions_defending[Situation::KickOff] = {{def}, {def}};
        set_piece_positions_attacking[Situation::KickOff] = {{att}, {att}};
    }

    {  // goal kick positions
        Vector3 def_left{0, pitch.getPointOfInterest(PitchPointsOfInterest::CenterSpot).y - 100};
        Vector3 att_left{0, pitch.getPointOfInterest(PitchPointsOfInterest::CenterSpot).y - 100};
        Vector3 def_right{0, pitch.getPointOfInterest(PitchPointsOfInterest::CenterSpot).y - 100};
        Vector3 att_right{0, pitch.getPointOfInterest(PitchPointsOfInterest::CenterSpot).y - 100};
        if (modifier_mask & modifier_left) {
            def_left.x = def_right.x = att_left.x = att_right.x =
                pitch.getPointOfInterest(PitchPointsOfInterest::CentercircleWest).x;
            def_left.x = def_right.x = att_left.x = att_right.x =
                pitch.getPointOfInterest(PitchPointsOfInterest::CentercircleWest).x;

        } else if (modifier_mask & modifier_right) {
            def_left.x = def_right.x = att_left.x = att_right.x =
                pitch.getPointOfInterest(PitchPointsOfInterest::CentercircleEast).x;
            def_left.x = def_right.x = att_left.x = att_right.x =
                pitch.getPointOfInterest(PitchPointsOfInterest::CentercircleEast).x;
        }
        def_left.x -= 200;
        att_left.x -= 200;
        def_right.x += 200;
        att_right.x += 200;
        clamp(def_left, def_right, att_left, att_right);
        set_piece_positions_defending[Situation::GoalKick] = {{def_left}, {def_right}};
        set_piece_positions_attacking[Situation::GoalKick] = {{att_left}, {att_right}};
    }
    {  // corner positions
        // todo: make this the posts
        Vector3 def{0, pitch.getPointOfInterest(PitchPointsOfInterest::Halfway, PitchPointOfInterestSide::North).y};
        Vector3 att{0, pitch.getPointOfInterest(PitchPointsOfInterest::Bye, PitchPointOfInterestSide::North).y - 60};
        if (modifier_mask & modifier_left) {
            def.x = pitch.getPointOfInterest(PitchPointsOfInterest::CentercircleWest).x - 20;
            att.x = pitch.getPointOfInterest(PitchPointsOfInterest::CenterSpot).x - 20;

        } else if (modifier_mask & modifier_right) {
            def.x = pitch.getPointOfInterest(PitchPointsOfInterest::CentercircleEast).x + 20;
            att.x = pitch.getPointOfInterest(PitchPointsOfInterest::CenterSpot).x + 20;
        }
        set_piece_positions_defending[Situation::Corner] = {{def}, {def}};
        set_piece_positions_attacking[Situation::Corner] = {{att}, {att}};
    }
}
//
//
//
Engine::Vector3 PositionCenterForward::getPlayingPosition(const Ball &in_ball) {
    Vector3 result;
    float middle = pitch.getDimensions().bounds.getSize().x / 2;

    Vector3 ball = pitch.toPitchSpace(in_ball.movable.position);
    // rotate perception of ball if attacking towards south
    if (my_team.getAttackingGoal() == Direction::South) {
        ball.rotate(180, pitch.getDimensions().bounds.getSize().x / 2, pitch.getDimensions().bounds.getSize().y / 2);
    }

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
    result = {out_x, other_team.gameplan.getDefensiveLine().y};

    // TODO
    if (my_team.getAttackingGoal() == Direction::South) {
        result.y += 100;
    } else {
        result.y -= 100;
    }

    // rotate left to right?
    if (my_team.getAttackingGoal() == Direction::South) {
        Vector3 tmp{result.x, 0};
        tmp.rotate(180, middle, 0);
        result.x = tmp.x;
    }

    return result;
}
