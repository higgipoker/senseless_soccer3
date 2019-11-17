#include "PositionWideMidfielder.hpp"
//
#include "Team.hpp"
//
using namespace Engine;
//
//
//
void PositionWideMidfielder::init() {
    set_piece_positions[Situation::KickOff] = {{}, {}};
}
//
//
//
Engine::Vector3 PositionWideMidfielder::getTargetPosition(const Situation in_situation, const Team &in_my_team,
                                                          const Team &in_other_team, const Ball &in_ball) {
    Vector3 ball = pitch.toPitchSpace(in_ball.movable.position);
    // rotate perception of ball if attacking towards south
    if (in_my_team.getAttackingGoal() == Direction::South) {
        ball.rotate(180, pitch.getDimensions().bounds.getSize().x / 2, pitch.getDimensions().bounds.getSize().y / 2);
    }

    float middle = pitch.getDimensions().bounds.getSize().x / 2;
    float ball_to_middle = ball.x - middle;
    float out_x = 0;
    switch (in_my_team.gameplan.defensive_width_type) {
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
    if (in_my_team.getAttackingGoal() == Direction::South) {
        {  // rotate on x
            Vector3 tmp{result.x, 0};
            tmp.rotate(180, middle, 0);
            result.x = tmp.x;
        }

        {  // rotate on y
            Vector3 tmp{0, result.y};
            tmp.rotate(180, 0, pitch.getDimensions().bounds.getSize().y/2);
            result.y = tmp.y;
        }
    }
    return pitch.toScreenSpace(result);
}
