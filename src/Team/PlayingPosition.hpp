#pragma once
#include "Ball/Ball.hpp"
#include "Pitch/Pitch.hpp"
//
#include "Engine/Vector.hpp"
namespace Senseless {
class Team;

enum class PositionModifier { Center, Left, Right, Attacking, Defensive };
enum class MarkingModifier { Zonal, Man, Tight, None };

const unsigned char modifier_none{0};            // 0000 0000
const unsigned char modifier_center{1 << 0};     // 0000 0001
const unsigned char modifier_left{1 << 1};       // 0000 0010
const unsigned char modifier_right{1 << 2};      // 0000 0100
const unsigned char modifier_attacking{1 << 3};  // 0000 1000
const unsigned char modifier_defensive{1 << 4};  // 0001 0000
const unsigned char modifier_unused1{1 << 5};    // 0010 0000
const unsigned char modifier_unused2{1 << 6};    // 0100 0000
const unsigned char modifier_unused3{1 << 7};    // 1000 0000

enum class Situation { Playing, KickOff, GoalKick, Corner, FreeKick, ThrowIn };

class PlayingPosition {
 public:
  /**
   * @brief PlayingPosition
   * @param in_pitch
   * @param in_my_team
   * @param in_other_team
   */
  PlayingPosition(const Pitch &in_pitch, const Team &in_my_team, const Team &in_other_team);
  /**
   * @brief init
   */
  virtual void init() = 0;
  /**
   * @brief getTargetPosition
   * @param in_situation
   * @param in_ball
   * @param in_pitch_side
   * @return
   */
  virtual Vector3 getTargetPosition(
      const Situation in_situation, const Ball &in_ball,
      const Direction in_pitch_side = Direction::West);
  /**
   * @brief getPlayingPosition
   * @param in_ball
   * @return
   */
  virtual Vector3 getPlayingPosition(const Ball &in_ball) = 0;
  /**
   * @brief getSetPiecePosition
   * @param in_situation
   * @param in_pitch_side
   * @return
   */
  Vector3 getSetPiecePosition(
      const Situation in_situation,
      const Direction in_pitch_side = Direction::West);
  /**
   * @brief applyModifier
   * @param in_mod
   */
  void applyModifier(const PositionModifier in_mod);
  std::map<Situation, std::pair<Vector3, Vector3>>
      set_piece_positions_defending;
  std::map<Situation, std::pair<Vector3, Vector3>>
      set_piece_positions_attacking;
  std::string name = "PlayingPosition";

 protected:
  const Pitch &pitch;
  const Team &my_team;
  const Team &other_team;
  MarkingModifier marking;
  unsigned char modifier_mask{modifier_none};
  static int instances;
  float min_x = 0;
  float max_x = 0;
  float min_y = 0;
  float max_y = 0;
  /**
   * @brief clamp
   * @param in_v1
   * @param in_v2
   * @param in_v3
   * @param in_v4
   */
  void clamp(Vector3 &in_v1, Vector3 &in_v2, Vector3 &in_v3,
             Vector3 &in_v4);
};
}  // namespace Senseless
