#include "PositionCenterMidfielder.hpp"
//
#include "Team.hpp"
//
using namespace Engine;
//
//
//
Engine::Vector3 PositionCenterMidfielder::getTargetPosition(const Pitch &in_pitch, const Team &in_my_team,
                                                            const Team &in_other_team, const Ball &in_ball) {
    Vector3 ball = in_pitch.toPitchSpace(in_ball.movable.position);
    // rotate perception of ball if attacking towards south
    if (in_my_team.getAttackingGoal() == Direction::South) {
        ball.rotate(180, in_pitch.getDimensions().bounds.getSize().x / 2, in_pitch.getDimensions().bounds.getSize().y / 2);
    }

    float middle = in_pitch.getDimensions().bounds.getSize().x / 2;
    float ball_to_middle = ball.x - middle;
    float out_x = 0;
    switch (in_my_team.gameplan.defensive_width_type) {
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
        constraint_width = in_pitch.getDimensions().bounds.getSize().x * 0.2F;
        min = middle - constraint_width;
        max = middle - constraint_width / 3;
    }
    if (modifier_mask & modifier_right) {
        constraint_width = in_pitch.getDimensions().bounds.getSize().x * 0.2F;
        min = middle + constraint_width / 3;
        max = middle + constraint_width;
    }
    out_x = std::clamp(out_x, min, max);
    float out_y = ball.y - 100;
    out_y = std::clamp(out_y, in_my_team.gameplan.getDefensiveLine().y, in_pitch.getDimensions().bounds.getSize().y);
    Vector3 result{out_x, ball.y - 100};

    // rotate for other side?
    if (in_my_team.getAttackingGoal() == Direction::South) {
        {  // rotate on x
            Vector3 tmp{result.x, 0};
            tmp.rotate(180, middle, 0);
            result.x = tmp.x;
        }

        {  // rotate on y
            Vector3 tmp{0, result.y};
            tmp.rotate(180, 0, in_pitch.getDimensions().bounds.getSize().y / 2);
            result.y = tmp.y;
        }
    }

    return in_pitch.toScreenSpace(result);
}
