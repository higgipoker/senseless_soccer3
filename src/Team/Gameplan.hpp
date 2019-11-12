#pragma once
#include "Ball/Ball.hpp"
#include "Pitch/Pitch.hpp"
//
//
//
enum class DefensiveLineType { Deep, Normal, High };
enum class DefensivewidthType { Narrow, Normal, Wide };
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
    Engine::Vector3  getDefensiveLine() const;
    //
    //
    //
    DefensiveLineType defensive_line_height = DefensiveLineType::Normal;
    DefensivewidthType defensive_width_type = DefensivewidthType::Narrow;

   private:
    //
    //
    //
    void updateDefensiveLine(const Pitch& in_pitch, const Ball& in_ball,
                             const Engine::Direction in_attacking_direction);
    //
    //
    //
    Engine::Vector3 defensive_line;

   public:
    friend class Team;
};
