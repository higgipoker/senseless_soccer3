#pragma once
#include "Ball/Ball.hpp"
#include "Pitch/Pitch.hpp"
//
//
//
enum class DefensiveLine { Deep, Normal, High };
//
//
//
class Gameplan {
   public:
    //
    //
    //
    Gameplan();
    //
    //
    //
    float getDefensiveLine(const Pitch& in_pitch, const Ball& in_ball, const Engine::Direction in_attacking_direction) const;
    //
    //
    //
    DefensiveLine defensive_line = DefensiveLine::Normal;
};
