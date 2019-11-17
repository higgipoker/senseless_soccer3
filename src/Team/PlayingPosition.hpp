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
    std::string name = "PlayingPosition";
    //
    //
    //
    PlayingPosition(const Pitch &in_pitch, const Team &in_my_team, const Team &in_other_team)
        : pitch(in_pitch), my_team(in_my_team), other_team(in_other_team) {
        ++instances;
        std::cout << instances << " positions" << std::endl;

        min_x = 0;
        max_x = pitch.getPointOfInterest(PitchPointsOfInterest::SideEast).x;
        min_y = 0;
        max_y = pitch.getPointOfInterest(PitchPointsOfInterest::Bye, PitchPointOfInterestSide::North).y;

        set_piece_positions_defending[Situation::Playing] = {{}, {}};
        set_piece_positions_defending[Situation::KickOff] = {{}, {}};
        set_piece_positions_defending[Situation::GoalKick] = {{}, {}};
        set_piece_positions_defending[Situation::Corner] = {{}, {}};
        set_piece_positions_defending[Situation::FreeKick] = {{}, {}};
        set_piece_positions_defending[Situation::ThrowIn] = {{}, {}};

        set_piece_positions_attacking[Situation::Playing] = {{}, {}};
        set_piece_positions_attacking[Situation::KickOff] = {{}, {}};
        set_piece_positions_attacking[Situation::GoalKick] = {{}, {}};
        set_piece_positions_attacking[Situation::Corner] = {{}, {}};
        set_piece_positions_attacking[Situation::FreeKick] = {{}, {}};
        set_piece_positions_attacking[Situation::ThrowIn] = {{}, {}};
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
    virtual Engine::Vector3 getTargetPosition(const Situation in_situation, const Ball &in_ball);
    //
    //
    //
    virtual Engine::Vector3 getPlayingPosition(const Situation in_situation, const Ball &in_ball) = 0;
    //
    //
    //
    Engine::Vector3 getSetPiecePosition(const Situation in_situation, const Ball &in_ball,
                                        const Engine::Direction in_pitch_side = Engine::Direction::West);

    //
    //
    //
    void applyModifier(const PositionModifier in_mod);
    //
    //
    //
    std::map<Situation, std::pair<Engine::Vector3, Engine::Vector3> > set_piece_positions_defending;
    std::map<Situation, std::pair<Engine::Vector3, Engine::Vector3> > set_piece_positions_attacking;
    //
    //
    //
   protected:
    const Pitch &pitch;
    const Team &my_team;
    const Team &other_team;
    unsigned char modifier_mask{modifier_none};
    static int instances;

    float min_x = 0;
    float max_x = 0;
    float min_y = 0;
    float max_y = 0;

    void clamp(Engine::Vector3 &in_v1, Engine::Vector3 &in_v2, Engine::Vector3 &in_v3, Engine::Vector3 &in_v4) {
        in_v1.x = std::clamp(in_v1.x, min_x, max_x);
        in_v1.y = std::clamp(in_v1.y, min_y, max_y);

        in_v2.x = std::clamp(in_v2.x, min_x, max_x);
        in_v2.y = std::clamp(in_v2.y, min_y, max_y);

        in_v3.x = std::clamp(in_v3.x, min_x, max_x);
        in_v3.y = std::clamp(in_v3.y, min_y, max_y);

        in_v4.x = std::clamp(in_v4.x, min_x, max_x);
        in_v4.y = std::clamp(in_v4.y, min_y, max_y);
    }
};
