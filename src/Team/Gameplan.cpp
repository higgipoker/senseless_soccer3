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
                                   const Engine::Direction in_attacking_direction) {
    Engine::Vector3 ball = in_pitch.toPitchSpace(in_ball.movable.position);

    //    if (in_attacking_direction == Engine::Direction::North) {
    //        ball_y = in_pitch.mirrorY(ball_y);
    //    }

    int min = 0;
    int max = in_pitch.dimensions.bounds.getSize().y / 2;
    int goal_to_ball = ball.y;

    switch (defensive_line_height) {
        case DefensiveLineType::Deep:
            defensive_line.y = std::clamp(min + (static_cast<int>(goal_to_ball * 0.4F)), min, max);
            break;
        case DefensiveLineType::Normal: {
            defensive_line.y = std::clamp(min + (static_cast<int>(goal_to_ball * 0.6F)), min, max);
        } break;
        case DefensiveLineType::High:
            defensive_line.y = std::clamp(min + (static_cast<int>(goal_to_ball * 0.8F)), min, max);
            break;
    }
    defensive_line = in_pitch.toScreenSpace(defensive_line);
}
//
//
//
float Gameplan::getDefensiveLine() const {
    return defensive_line.y;
}
