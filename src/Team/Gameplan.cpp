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
void Gameplan::updateDefensiveLine(const Pitch &in_pitch, const Ball &in_ball,
                                 const Engine::Direction in_attacking_direction)  {

    int ball_y = in_ball.movable.position.y;

    if (in_attacking_direction == Engine::Direction::North) {
        ball_y = in_pitch.mirrorY(ball_y);
    }

    int min = in_pitch.dimensions.bounds.getPosition().y;
    int max = in_pitch.dimensions.halfway_line.getPosition().y;
    int goal_to_ball = ball_y - min;

    switch (defensive_line_height) {
        case DefensiveLineType::Deep:
            defensive_line = std::clamp(min + (static_cast<int>(goal_to_ball * 0.4F)), min, max);
            break;
        case DefensiveLineType::Normal: {
            defensive_line = std::clamp(min + (static_cast<int>(goal_to_ball * 0.6F)), min, max);
        } break;
        case DefensiveLineType::High:
            defensive_line = std::clamp(min + (static_cast<int>(goal_to_ball * 0.8F)), min, max);
            break;
    }

    if (in_attacking_direction == Engine::Direction::North) {
        defensive_line = in_pitch.mirrorY(defensive_line);
    }
}
//
//
//
float Gameplan::getDefensiveLine() const{
    return defensive_line;
}
