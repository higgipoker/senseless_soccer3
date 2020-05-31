#pragma once
//
#include "Engine/Entity.hpp"
#include "MiniMapSprite.h"

#include "Team/Team.hpp"
#include "Ball/Ball.hpp"
#include "Engine/Camera.hpp"
#include "Pitch.hpp"
//
namespace Senseless {
//
//
//
class MiniMap : public Entity {
 public:
  void    update      (const float in_dt) override;
  MiniMapSprite& getSprite() { return static_cast<MiniMapSprite&>(*renderable.sprite); }

 private:
  MiniMap(Team& in_home_team, Team& in_away_team, Ball& in_ball, Pitch& in_pitch, Camera& in_camera);
  Team& home_team;
  Team& away_team;
  Ball& ball;
  Pitch& pitch;
  Camera& camera;

 public:
  friend class EntityFactory;
};
}  // namespace Senseless
