#include "Gameplan.hpp"

#include <algorithm>
//
//
//
Gameplan::Gameplan() {

}
//
//
//
float Gameplan::getDefensiveLine(const Pitch &in_pitch, const Ball &in_ball, const Engine::Direction in_attacking_direction) const{
    float line = 0;

    int ball_y = in_ball.movable.position.y;

    if(in_attacking_direction == Engine::Direction::NORTH){
        ball_y = in_pitch.mirrorY(ball_y);
    }

    int min = in_pitch.dimensions.bounds.getPosition().y;
    int max = in_pitch.dimensions.halfway_line.getPosition().y;
    int goal_to_ball = ball_y - min;

    switch (defensive_line) {
        case DefensiveLine::Deep:
            line = std::clamp(min + (static_cast<int>(goal_to_ball * 0.4F)), min, max);
            break;
        case DefensiveLine::Normal: {
            line = std::clamp(min + (static_cast<int>(goal_to_ball * 0.6F)), min, max);
        } break;
        case DefensiveLine::High:
            line = std::clamp(min + (static_cast<int>(goal_to_ball * 0.8F)), min, max);
            break;
    }

    if(in_attacking_direction == Engine::Direction::NORTH){
        line = in_pitch.mirrorY(line);
    }
    return line;
}
