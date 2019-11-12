#include "PositionFullBack.hpp"
//
#include "Team.hpp"
//
using namespace Engine;
//
//
//
Engine::Vector3 PositionFullBack::getTargetPosition(const Pitch &in_pitch, const Team &in_my_team,
                                                    const Team &in_other_team, const Ball &in_ball) {
    float out_x = 0;
    float middle = in_pitch.dimensions.bounds.getSize().x / 2;
    float min = 0;
    float max = 0;

    Vector3 ball = in_pitch.toPitchSpace(in_ball.movable.position);
    // rotate perception of ball if attacking towards south
    if (in_my_team.getAttackingGoal() == Direction::South) {
        ball.rotate(180, in_pitch.dimensions.bounds.getSize().x / 2, in_pitch.dimensions.bounds.getSize().y / 2);
    }
    float ball_to_middle = ball.x - middle;

    // within 20% of the middle of the pitch
    float sec_10 = in_pitch.dimensions.bounds.getSize().x * 0.1F;
    min = middle - sec_10;
    max = middle + sec_10;

    if (modifier_mask & modifier_left) {
        // within left left quarter
        sec_10 = in_pitch.dimensions.bounds.getSize().x * 0.25F;
        min = 0;
        max = sec_10;
    }
    if (modifier_mask & modifier_right) {
        // within right right quarter
        sec_10 = in_pitch.dimensions.bounds.getSize().x * 0.25F;
        min = in_pitch.dimensions.bounds.getSize().x - sec_10;
        max = in_pitch.dimensions.bounds.getSize().x;
    }

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
    out_x = std::clamp(out_x, min, max);

    Vector3 result{out_x, in_my_team.gameplan.getDefensiveLine().y};
    if (in_my_team.getAttackingGoal() == Direction::South) {
        // since the team y defensive line has already been calced, only rotate x here
        Vector3 tmp{result.x, 0};
        tmp.rotate(180, middle, 0);
        result.x = tmp.x;
    }

    return in_pitch.toScreenSpace(result);
}
