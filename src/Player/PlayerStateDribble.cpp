#include "PlayerStateDribble.hpp"

#include <iostream>

#include "Engine/Collider.hpp"
#include "Engine/Compass.hpp"
#include "Match/Match.hpp"
#include "Player.hpp"

// tmp lookup for kick force needed depeinding on player speed

namespace Senseless {
//
//
//
PlayerStateDribble::PlayerStateDribble(Player &in_player) : PlayerState(in_player) {
  name = "Dribble";
}
//
//
//
void PlayerStateDribble::start() {
  player.match.player_in_possession = &player;
  player.ball_under_control = true;
  already_kicked = false;
  player.current_speed = dribble_speeds[player.speed];
}
//
//
//
void PlayerStateDribble::close_control() {
  already_kicked = false;
  // edge of feet circle in direction of movement
  Vector3 ball_position{player.feet.getCenter()};
  Vector3 offset = player.facing.toVector() *
                   (player.feet.getRadius() + player.match.getBall().collidable.getRadius());
  ball_position += offset * 1.f;

  // put the ball there
  player.match.getBall().movable.place(ball_position);
}
//
//
//
void PlayerStateDribble::step() {
  PlayerState::step();

  // check for changed direction (close control)
  Compass old_direction = player.facing;
  Vector3 dir = player.movable.velocity;
  player.facing.fromVector(dir);
  if (old_direction.direction != player.facing.direction) {
    close_control();
  } else {
    // check for collision with ball
    if (Collider::collides(player.feet, player.match.getBall().collidable)) {
      if (!already_kicked) {
        kick();
      }
    } else {
      already_kicked = false;
    }
  }

  player.player_sprite.setPlayerAnimation(PlayerAnimationType::Run, player.facing.direction);

  player.calc_short_pass_candidates();
}
//
//
//
void PlayerStateDribble::stop() {
  if (player.match.player_in_possession == &player) {
    player.match.player_in_possession = nullptr;
  }
  player.ball_under_control = false;
}
//
//
//
bool PlayerStateDribble::stateOver() {
  // check if ball is outside control range
  if (!player.ballInControlRange()) {
    next_state = player_state::Run;
    return true;
  }
  // or if we stopped moving
  if (Math::equal(player.movable.velocity.magnitude2d(), 0)) {
    next_state = player_state::Stand;
    return true;
  }

  return false;
}
//
//
//
void PlayerStateDribble::kick() {
  already_kicked = true;
  float force = kick_mods[static_cast<RunningSpeed>(player.speed)];
  auto f = player.movable.velocity.magnitude2d();
  f++;
  Vector3 kick_force = Compass(player.facing).toVector();
  kick_force.normalise2d();
  kick_force *= force;
  player.match.getBall().kick(kick_force);
}
}  // namespace Senseless
