#include "PositionCenterBack.hpp"
//
#include "Team.hpp"
//
namespace Senseless {
//
//
//
void PositionCenterBack::init() {
    {
        // kick off positions
        sf::Vector3f def_left{0, pitch.getPointOfInterest (PitchPointsOfInterest::CenterSpot).y * 0.35F, 0};
        sf::Vector3f def_right{0, pitch.getPointOfInterest (PitchPointsOfInterest::CenterSpot).y * 0.35F, 0};
        sf::Vector3f att_left{0, pitch.getPointOfInterest (PitchPointsOfInterest::CenterSpot).y * 0.55F, 0};
        sf::Vector3f att_right{0, pitch.getPointOfInterest (PitchPointsOfInterest::CenterSpot).y * 0.55F, 0};
        if (modifier_mask & modifier_left) {
            def_left.x = def_right.x = att_left.x = att_right.x =
                                                        pitch.getPointOfInterest (PitchPointsOfInterest::CentercircleWest).x;

        } else if (modifier_mask & modifier_right) {
            def_left.x = def_right.x = att_left.x = att_right.x =
                                                        pitch.getPointOfInterest (PitchPointsOfInterest::CentercircleEast).x;
        }

        clamp (def_left, def_right, att_left, att_right);

        set_piece_positions_defending[Situation::KickOff] = {{def_left}, {def_right}};
        set_piece_positions_attacking[Situation::KickOff] = {{att_left}, {att_right}};
    }

    {
        // goal kick positions
        sf::Vector3f def_left{0, pitch.getPointOfInterest (PitchPointsOfInterest::Eighteen).y, 0};
        sf::Vector3f def_right{0, pitch.getPointOfInterest (PitchPointsOfInterest::Eighteen).y, 0};
        sf::Vector3f att_left{0, pitch.getPointOfInterest (PitchPointsOfInterest::Eighteen).y, 0};
        sf::Vector3f att_right{0, pitch.getPointOfInterest (PitchPointsOfInterest::Eighteen).y, 0};
        if (modifier_mask & modifier_left) {
            def_left.x = def_right.x = att_left.x = att_right.x =
                                                        pitch.getPointOfInterest (PitchPointsOfInterest::CenterSpot).x - 100;

        } else if (modifier_mask & modifier_right) {
            def_left.x = def_right.x = att_left.x = att_right.x =
                                                        pitch.getPointOfInterest (PitchPointsOfInterest::CenterSpot).x + 100;
        }

        def_left.x -= 200;
        att_left.x -= 200;
        def_right.x += 200;
        att_right.x += 200;
        clamp (def_left, def_right, att_left, att_right);

        set_piece_positions_defending[Situation::GoalKick] = {{def_left}, {def_right}};
        set_piece_positions_attacking[Situation::GoalKick] = {{att_left}, {att_right}};
    }
    {
        // corner positions
        sf::Vector3f def_left{0, pitch.getPointOfInterest (PitchPointsOfInterest::Bye).y + 50, 0};
        sf::Vector3f def_right{0, pitch.getPointOfInterest (PitchPointsOfInterest::Bye).y + 50, 0};
        sf::Vector3f att_left{0, pitch.getPointOfInterest (PitchPointsOfInterest::CenterSpot).y, 0};
        sf::Vector3f att_right{0, pitch.getPointOfInterest (PitchPointsOfInterest::CenterSpot).y, 0};
        if (modifier_mask & modifier_left) {
            def_left.x = def_right.x = att_left.x = att_right.x =
                                                        pitch.getPointOfInterest (PitchPointsOfInterest::PenaltySpot).x - 25;

        } else if (modifier_mask & modifier_right) {
            def_left.x = def_right.x = att_left.x = att_right.x =
                                                        pitch.getPointOfInterest (PitchPointsOfInterest::PenaltySpot).x + 25;
        }
        clamp (def_left, def_right, att_left, att_right);
        set_piece_positions_defending[Situation::Corner] = {{def_left}, {def_right}};
        set_piece_positions_attacking[Situation::Corner] = {{att_left}, {att_right}};
    }
}
//
//
//
sf::Vector3f PositionCenterBack::getPlayingPosition (const Ball &in_ball) {
    sf::Vector3f ball = in_ball.movable.position;
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
    out_x = std::clamp (out_x, min, max);
    sf::Vector3f result{out_x, my_team.gameplan.getDefensiveLine().y, 0};

    // rotate for other side?
    if (my_team.getAttackingGoal() == Direction::South) {
        // since the team y defensive line has already been calced, only rotate x here
        sf::Vector3f tmp{result.x, 0, 0};
        Vector::rotate (tmp, 0, middle, 0);
        result.x = tmp.x;
    }

    return result;
}
}  // namespace Senseless
