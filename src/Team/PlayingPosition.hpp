#pragma once
#include "Ball/Ball.hpp"
#include "Pitch/Pitch.hpp"
//
#include "Engine/Vector.hpp"
//
//
//
class Team;
//
//
//
enum class PositionModifier { Center, Left, Right, Attacking, Defensive };
//
//
//
const unsigned char modifier_none{0};            // 0000 0001
const unsigned char modifier_center{1 << 0};     // 0000 0001
const unsigned char modifier_left{1 << 1};       // 0000 0010
const unsigned char modifier_right{1 << 2};      // 0000 0100
const unsigned char modifier_attacking{1 << 3};  // 0000 1000
const unsigned char modifier_defensive{1 << 4};  // 0001 0000
const unsigned char modifier_unused1{1 << 5};    // 0010 0000
const unsigned char modifier_unused2{1 << 6};    // 0100 0000
const unsigned char modifier_unused3{1 << 7};    // 1000 0000
//
//
//
class PlayingPosition {
   public:
    //
    //
    //
    PlayingPosition() {
        ++instances;
        std::cout << instances << " positions" << std::endl;
    }
    //
    //
    //
    ~PlayingPosition() {
        --instances;
        std::cout << instances << " positions" << std::endl;
    }
    //
    //
    //
    virtual Engine::Vector3 getTargetPosition(const Pitch &in_pitch, const Team &in_my_team, const Team &in_other_team,
                                              const Ball &in_ball) = 0;
    //
    //
    //
    void applyModifier(const PositionModifier in_mod);

   protected:
    unsigned char modifier_mask{modifier_none};
    static int instances;
};
