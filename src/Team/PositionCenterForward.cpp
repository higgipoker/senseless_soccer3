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
        Vector3 def{0, pitch.getDimensions().halfway_line.getPosition().y - 50};
        Vector3 att{0, pitch.getDimensions().halfway_line.getPosition().y};
        if (modifier_mask & modifier_left) {
            def.x = att.x =
                pitch.getDimensions().bounds.getSize().x / 2 - pitch.getDimensions().center_circle.getRadius();

        } else if (modifier_mask & modifier_right) {
            def.x = att.x =
                pitch.getDimensions().bounds.getSize().x / 2 + pitch.getDimensions().center_circle.getRadius();
        }
        set_piece_positions[Situation::KickOff] = {{def}, {att}};
    }
}
//
//
//
Engine::Vector3 PositionCenterForward::getPlayingPosition(const Situation in_situation, const Team &in_my_team,
                                                          const Team &in_other_team, const Ball &in_ball) {
    Vector3 result;
    float middle = pitch.getDimensions().bounds.getSize().x / 2;

    Vector3 ball = pitch.toPitchSpace(in_ball.movable.position);
    // rotate perception of ball if attacking towards south
    if (in_my_team.getAttackingGoal() == Direction::South) {
        ball.rotate(180, pitch.getDimensions().bounds.getSize().x / 2, pitch.getDimensions().bounds.getSize().y / 2);
    }

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
    result = {out_x, in_other_team.gameplan.getDefensiveLine().y};
    result.y -= 100;

    // rotate left to right?
    if (in_my_team.getAttackingGoal() == Direction::South) {
        Vector3 tmp{result.x, 0};
        tmp.rotate(180, middle, 0);
        result.x = tmp.x;
    }

    return pitch.toScreenSpace(result);
}
