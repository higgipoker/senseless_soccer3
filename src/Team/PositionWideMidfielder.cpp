#include "PositionWideMidfielder.hpp"
//
#include "Team.hpp"
//
using namespace Engine;
//
//
//
void PositionWideMidfielder::init() {
    {  // kick off positions
        Vector3 def{0, pitch.getPointOfInterest(PitchPointsOfInterest::CenterSpot).y * 0.65F};
        Vector3 att{0, pitch.getPointOfInterest(PitchPointsOfInterest::CenterSpot).y * 0.85F};
        if (modifier_mask & modifier_left) {
            def.x = att.x = pitch.getPointOfInterest(PitchPointsOfInterest::SideWest).x + 200;

        } else if (modifier_mask & modifier_right) {
            def.x = att.x = pitch.getPointOfInterest(PitchPointsOfInterest::SideEast).x - 200;
        }
        set_piece_positions_defending[Situation::KickOff] = {{def}, {def}};
        set_piece_positions_attacking[Situation::KickOff] = {{att}, {att}};
    }

    {  // goal kick positions
        Vector3 def_left{0, pitch.getPointOfInterest(PitchPointsOfInterest::Halfway).y * 0.6F};
        Vector3 att_left{0, pitch.getPointOfInterest(PitchPointsOfInterest::Halfway).y * 0.6F};
        Vector3 def_right{0, pitch.getPointOfInterest(PitchPointsOfInterest::Halfway).y * 0.6F};
        Vector3 att_right{0, pitch.getPointOfInterest(PitchPointsOfInterest::Halfway).y * 0.6F};
        if (modifier_mask & modifier_left) {
            def_left.x = def_right.x = att_left.x = att_right.x =
                pitch.getPointOfInterest(PitchPointsOfInterest::SideWest).x + 100;

        } else if (modifier_mask & modifier_right) {
            def_left.x = def_right.x = att_left.x = att_right.x =
                pitch.getPointOfInterest(PitchPointsOfInterest::SideEast).x - 100;
        }
        const int offset = 300;
        def_left.x -= offset;
        att_left.x -= offset;
        def_right.x += offset;
        att_right.x += offset;
        clamp(def_left, def_right, att_left, att_right);

        set_piece_positions_defending[Situation::GoalKick] = {{def_left}, {def_right}};
        set_piece_positions_attacking[Situation::GoalKick] = {{att_left}, {att_right}};
    }
    {  // corner
        Vector3 def_left{0,
                         pitch.getPointOfInterest(PitchPointsOfInterest::Eighteen, PitchPointOfInterestSide::South).y};
        Vector3 att_left{0,
                         pitch.getPointOfInterest(PitchPointsOfInterest::Eighteen, PitchPointOfInterestSide::North).y};
        Vector3 def_right{0,
                          pitch.getPointOfInterest(PitchPointsOfInterest::Eighteen, PitchPointOfInterestSide::South).y};
        Vector3 att_right{0,
                          pitch.getPointOfInterest(PitchPointsOfInterest::Eighteen, PitchPointOfInterestSide::North).y};
        if (modifier_mask & modifier_left) {
            def_left.x = def_right.x = pitch.getPointOfInterest(PitchPointsOfInterest::EighteenArcWest).x;
            att_left.x = att_right.x = pitch.getPointOfInterest(PitchPointsOfInterest::SideWest).x + 100;

        } else if (modifier_mask & modifier_right) {
            def_left.x = def_right.x = pitch.getPointOfInterest(PitchPointsOfInterest::EighteenArcEast).x;
            att_left.x = att_right.x = pitch.getPointOfInterest(PitchPointsOfInterest::SideEast).x - 100;
        }
        const int offset = 300;
        att_left.x -= offset;
        att_right.x += offset;
        clamp(def_left, def_right, att_left, att_right);

        set_piece_positions_defending[Situation::Corner] = {{def_left}, {def_right}};
        set_piece_positions_attacking[Situation::Corner] = {{att_left}, {att_right}};
    }
}
//
//
//
Engine::Vector3 PositionWideMidfielder::getPlayingPosition(const Situation in_situation, const Ball &in_ball) {
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
            out_x = middle + ball_to_middle * 1.0F;
            break;
        case DefensivewidthType::Normal:
            out_x = middle + ball_to_middle * 1.5F;
            break;
        case DefensivewidthType::Wide:
            out_x = middle + ball_to_middle * 2.0F;
            break;
    }

    // constrain
    float min = 0;
    float max = 0;
    float constraint_width = 0;
    if (modifier_mask & modifier_left) {
        constraint_width = pitch.getDimensions().bounds.getSize().x * 0.25F;
        min = 0;
        max = constraint_width;
    }
    if (modifier_mask & modifier_right) {
        constraint_width = pitch.getDimensions().bounds.getSize().x * 0.25F;
        min = pitch.getDimensions().bounds.getSize().x - constraint_width;
        max = pitch.getDimensions().bounds.getSize().x;
    }
    out_x = std::clamp(out_x, min, max);
    Vector3 result{out_x, ball.y - 100};

    // rotate for other side?
    if (my_team.getAttackingGoal() == Direction::South) {
        {  // rotate on x
            Vector3 tmp{result.x, 0};
            tmp.rotate(180, middle, 0);
            result.x = tmp.x;
        }

        {  // rotate on y
            Vector3 tmp{0, result.y};
            tmp.rotate(180, 0, pitch.getDimensions().bounds.getSize().y / 2);
            result.y = tmp.y;
        }
    }
    return result;
}