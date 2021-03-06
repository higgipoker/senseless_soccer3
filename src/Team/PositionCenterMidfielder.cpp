#include "PositionCenterMidfielder.hpp"
//
#include "Team.hpp"
//
namespace Senseless {
//
//
//
void PositionCenterMidfielder::init() {
  {  // kick off positions
    sf::Vector3f def{0, pitch.getPointOfInterest(PitchPointsOfInterest::CenterSpot).y * 0.65F, 0};
    sf::Vector3f att{0, pitch.getPointOfInterest(PitchPointsOfInterest::CenterSpot).y * 0.75F, 0};
    if (modifier_mask & modifier_left) {
      def.x = att.x = pitch.getPointOfInterest(PitchPointsOfInterest::CentercircleWest).x;

    } else if (modifier_mask & modifier_right) {
      def.x = att.x = pitch.getPointOfInterest(PitchPointsOfInterest::CentercircleEast).x;
    }
    set_piece_positions_defending[Situation::KickOff] = {{def}, {def}};
    set_piece_positions_attacking[Situation::KickOff] = {{att}, {att}};
  }

  {  // goal kick positions
    sf::Vector3f def_left{0, pitch.getPointOfInterest(PitchPointsOfInterest::Halfway).y * 0.6F, 0};
    sf::Vector3f att_left{0, pitch.getPointOfInterest(PitchPointsOfInterest::Halfway).y * 0.6F, 0};
    sf::Vector3f def_right{0, pitch.getPointOfInterest(PitchPointsOfInterest::Halfway).y * 0.6F, 0};
    sf::Vector3f att_right{0, pitch.getPointOfInterest(PitchPointsOfInterest::Halfway).y * 0.6F, 0};
    if (modifier_mask & modifier_left) {
      def_left.x = def_right.x = att_left.x = att_right.x =
          pitch.getPointOfInterest(PitchPointsOfInterest::CenterSpot).x - 100;

    } else if (modifier_mask & modifier_right) {
      def_left.x = def_right.x = att_left.x = att_right.x =
          pitch.getPointOfInterest(PitchPointsOfInterest::CenterSpot).x + 100;
    }
    def_left.x -= 200;
    att_left.x -= 200;
    def_right.x += 200;
    att_right.x += 200;
    clamp(def_left, def_right, att_left, att_right);
    set_piece_positions_defending[Situation::GoalKick] = {{def_left}, {def_right}};
    set_piece_positions_attacking[Situation::GoalKick] = {{att_left}, {att_right}};
  }
  {  // corner
    sf::Vector3f def{
        0, pitch.getPointOfInterest(PitchPointsOfInterest::Six, PitchPointOfInterestSide::South).y, 0};
    sf::Vector3f att{
        0,
        pitch.getPointOfInterest(PitchPointsOfInterest::Eighteen, PitchPointOfInterestSide::North)
            .y, 0};
    if (modifier_mask & modifier_left) {
      def.x = att.x = pitch.getPointOfInterest(PitchPointsOfInterest::CentercircleWest).x;

    } else if (modifier_mask & modifier_right) {
      def.x = att.x = pitch.getPointOfInterest(PitchPointsOfInterest::CentercircleEast).x;
    }
    set_piece_positions_defending[Situation::Corner] = {{def}, {def}};
    set_piece_positions_attacking[Situation::Corner] = {{att}, {att}};
  }
}
//
//
//
sf::Vector3f PositionCenterMidfielder::getPlayingPosition(const Ball &in_ball) {
  sf::Vector3f ball = in_ball.movable.position;
  // rotate perception of ball if attacking towards south
  if (my_team.getAttackingGoal() == Direction::South) {
    Vector::rotate(ball, 180, pitch.getDimensions().bounds.getSize().x / 2,
                pitch.getDimensions().bounds.getSize().y / 2);
  }

  float middle = pitch.getDimensions().bounds.getSize().x / 2;
  float ball_to_middle = ball.x - middle;
  float out_x = 0;
  switch (my_team.gameplan.defensive_width_type) {
    case DefensivewidthType::Narrow:
      out_x = middle + ball_to_middle * 0.3F;
      break;
    case DefensivewidthType::Normal:
      out_x = middle + ball_to_middle * 0.6F;
      break;
    case DefensivewidthType::Wide:
      out_x = middle + ball_to_middle * 1.0F;
      break;
  }

  // constrain
  float min = 0;
  float max = 0;
  float constraint_width = 0;
  if (modifier_mask & modifier_left) {
    constraint_width = pitch.getDimensions().bounds.getSize().x * 0.2F;
    min = middle - constraint_width;
    max = middle - constraint_width / 3;
  }
  if (modifier_mask & modifier_right) {
    constraint_width = pitch.getDimensions().bounds.getSize().x * 0.2F;
    min = middle + constraint_width / 3;
    max = middle + constraint_width;
  }
  out_x = std::clamp(out_x, min, max);
  float out_y = ball.y - 100;
  out_y = std::clamp(out_y, my_team.gameplan.getDefensiveLine().y,
                     pitch.getDimensions().bounds.getSize().y);
  sf::Vector3f result{out_x, ball.y - 100, 0};

  // rotate for other side?
  if (my_team.getAttackingGoal() == Direction::South) {
    {  // rotate on x
      sf::Vector3f tmp{result.x, 0, 0};
      Vector::rotate(tmp, 180, middle, 0);
      result.x = tmp.x;
    }

    {  // rotate on y
      sf::Vector3f tmp{0, result.y, 0};
      Vector::rotate(tmp, 180, 0, pitch.getDimensions().bounds.getSize().y / 2);
      result.y = tmp.y;
    }
  }

  return result;
}
}  // namespace Senseless
