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
enum class Situation { Playing, KickOff, GoalKick, Corner, FreeKick, ThrowIn };
//
//
//
class PlayingPosition {
    //
    //
    //
   public:
    //
    //
    //
    PlayingPosition(const Pitch &in_pitch) : pitch(in_pitch) {
        ++instances;
        std::cout << instances << " positions" << std::endl;

        set_piece_positions[Situation::Playing] = {{}, {}};
        set_piece_positions[Situation::KickOff] = {{}, {}};
        set_piece_positions[Situation::GoalKick] = {{}, {}};
        set_piece_positions[Situation::Corner] = {{}, {}};
        set_piece_positions[Situation::FreeKick] = {{}, {}};
        set_piece_positions[Situation::ThrowIn] = {{}, {}};
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
    virtual void init() = 0;
    //
    //
    //
    virtual Engine::Vector3 getTargetPosition(const Situation in_situation, const Team &in_my_team,
                                              const Team &in_other_team, const Ball &in_ball);
    //
    //
    //
    virtual Engine::Vector3 getPlayingPosition(const Situation in_situation, const Team &in_my_team,
                                               const Team &in_other_team, const Ball &in_ball) = 0;
    //
    //
    //
    Engine::Vector3 getSetPiecePosition(const Situation in_situation, const Team &in_my_team,
                                                const Team &in_other_team, const Ball &in_ball);

    //
    //
    //
    void applyModifier(const PositionModifier in_mod);
    //
    //
    //
    std::map<Situation, std::pair<Engine::Vector3, Engine::Vector3> > set_piece_positions;
    //
    //
    //
   protected:
    const Pitch &pitch;
    unsigned char modifier_mask{modifier_none};
    static int instances;
};
