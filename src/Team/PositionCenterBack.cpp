#include "PositionCenterBack.hpp"
//
#include "Team.hpp"
//
using namespace Engine;
//
//
//
Engine::Vector3 PositionCenterBack::getTargetPosition(const Pitch &in_pitch, const Team &in_my_team,
                                                      const Team &in_other_team, const Ball &in_ball) {
    float out_x = 0;
    float ball_x = in_ball.movable.position.x;
    float middle = in_pitch.dimensions.center_spot.getPosition().x;
    float ball_to_middle = ball_x - middle;
    float min = 0;
    float max = 0;

    if (modifier_mask & modifier_center) {
        // within 20% of the middle of the pitch
        float sec_20 = in_pitch.dimensions.bounds.getSize().x / 10;
        min = middle - sec_20;
        max = middle + sec_20;

    } else if (modifier_mask & modifier_right) {
        // within inner left 2 fifths
        float sec_20 = in_pitch.dimensions.bounds.getSize().x / 5;
        min = middle - sec_20;
        max = middle;
    }

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
    out_x = std::clamp(out_x, min, max);

    return {out_x, in_my_team.gameplan.getDefensiveLine()};
}
