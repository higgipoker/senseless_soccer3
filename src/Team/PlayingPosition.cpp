#include "PlayingPosition.hpp"
//
#include "Team.hpp"
//
namespace Senseless {
//
int PlayingPosition::instances = 0;
//
//
//
void PlayingPosition::clamp(Vector3 &in_v1, Vector3 &in_v2,
                            Vector3 &in_v3, Vector3 &in_v4) {
  in_v1.x = std::clamp(in_v1.x, min_x, max_x);
  in_v1.y = std::clamp(in_v1.y, min_y, max_y);

  in_v2.x = std::clamp(in_v2.x, min_x, max_x);
  in_v2.y = std::clamp(in_v2.y, min_y, max_y);

  in_v3.x = std::clamp(in_v3.x, min_x, max_x);
  in_v3.y = std::clamp(in_v3.y, min_y, max_y);

  in_v4.x = std::clamp(in_v4.x, min_x, max_x);
  in_v4.y = std::clamp(in_v4.y, min_y, max_y);
}
//
//
//
PlayingPosition::PlayingPosition(const Pitch &in_pitch, const Team &in_my_team,
                                 const Team &in_other_team)
    : pitch(in_pitch), my_team(in_my_team), other_team(in_other_team) {
  ++instances;
  // std::cout << instances << " positions" << std::endl;

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
void PlayingPosition::applyModifier(const PositionModifier in_mod) {
  switch (in_mod) {
    case PositionModifier::Center:
      modifier_mask |= modifier_center;
      break;
    case PositionModifier::Left:
      modifier_mask |= modifier_left;
      break;
    case PositionModifier::Right:
      modifier_mask |= modifier_right;
      break;
    case PositionModifier::Attacking:
      modifier_mask |= modifier_attacking;
      break;
    case PositionModifier::Defensive:
      modifier_mask |= modifier_defensive;
      break;
  }
  init();
}
//
//
//
Vector3 PlayingPosition::getTargetPosition(const Situation in_situation,
                                                      const Ball &in_ball,
                                                      const Direction in_pitch_side) {
  Vector3 result;
  switch (in_situation) {
    case Situation::Playing:
      result = getPlayingPosition(in_ball);
      break;
    case Situation::KickOff:
    case Situation::GoalKick:
    case Situation::Corner:
    case Situation::FreeKick:
    case Situation::ThrowIn:
      result = getSetPiecePosition(in_situation, in_pitch_side);
      // rotate for other side?
      if (my_team.getAttackingGoal() == Direction::South) {
        // since the team y defensive line has already been calced, only rotate x
        // here
        Vector3 tmp{result.x, 0};
        tmp.rotate(180, pitch.getPointOfInterest(PitchPointsOfInterest::CenterSpot).x, 0);
        result.x = tmp.x;
      }
      break;
  }
  return pitch.toScreenSpace(result);
}
//
//
//
Vector3 PlayingPosition::getSetPiecePosition(const Situation in_situation,
                                                        const Direction in_pitch_side) {
  Vector3 result;
  switch (my_team.getAttackingState()) {
    case AttackingState::Defending:
      if (in_pitch_side == Direction::West) {
        result = set_piece_positions_defending[in_situation].first;
      } else {
        result = set_piece_positions_defending[in_situation].second;
      }
      break;
    case AttackingState::Attacking:
      if (in_pitch_side == Direction::West) {
        result = set_piece_positions_attacking[in_situation].first;
      } else {
        result = set_piece_positions_attacking[in_situation].second;
      }
      break;
  }
  // rotate south->north?
  if (my_team.getAttackingGoal() == Direction::South) {
    Vector3 tmp{0, result.y};
    tmp.rotate(180, 0, pitch.getDimensions().halfway_line.getPosition().y);
    result.y = tmp.y;
  }
  return result;
}
}  // namespace Senseless
