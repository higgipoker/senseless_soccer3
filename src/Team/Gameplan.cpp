#include "Gameplan.hpp"

#include <algorithm>
//
using namespace Engine;
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

    // rotate perception of ball if attacking towards south
    if (in_attacking_direction == Direction::South) {
        ball.rotate(180, in_pitch.dimensions.bounds.getSize().x / 2, in_pitch.dimensions.bounds.getSize().y / 2);
    }

    const float min = 0;                                           // goal line
    const float max = in_pitch.dimensions.bounds.getSize().y / 2;  // half way line

    switch (defensive_line_height) {
        case DefensiveLineType::Deep:
            defensive_line.y = std::clamp(min + (static_cast<int>(ball.y * 0.4F)), min, max);
            break;
        case DefensiveLineType::Normal: {
            defensive_line.y = std::clamp(min + (static_cast<int>(ball.y * 0.6F)), min, max);
        } break;
        case DefensiveLineType::High:
            defensive_line.y = std::clamp(min + (static_cast<int>(ball.y * 0.8F)), min, max);
            break;
    }

    // rotate for attacking south
    if (in_attacking_direction == Direction::South) {
        defensive_line.y = in_pitch.dimensions.bounds.getSize().y - defensive_line.y;
        std::cout << defensive_line.y << std::endl;
    }
}
//
//
//
Vector3 Gameplan::getDefensiveLine() const {
    return defensive_line;
}
