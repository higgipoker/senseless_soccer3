#pragma once
//
#include "Ball/Ball.hpp"
#include "Engine/Camera.hpp"
#include "Engine/Entity.hpp"
#include "MiniMapSprite.h"
#include "Pitch.hpp"
#include "Team/Team.hpp"
//
namespace Senseless {
//
//
//
class MiniMap : public Entity {
 public:
  MiniMap(Team& in_home_team, Team& in_away_team, Ball& in_ball,
          Pitch& in_pitch, Camera& in_camera);
  void update(const float in_dt) override;
  MiniMapSprite& getSprite();

 private:
  Team& home_team;
  Team& away_team;
  Ball& ball;
  Pitch& pitch;
  Camera& camera;
};
}  // namespace Senseless
