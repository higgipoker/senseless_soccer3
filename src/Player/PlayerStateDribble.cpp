#include "PlayerStateDribble.hpp"

#include "Match/Match.hpp"
#include "Player.hpp"

#include "Engine/Collider.hpp"
#include "Engine/Compass.hpp"

#include <iostream>

// tmp lookup for kick force needed depeinding on player speed

using namespace Engine;
//
//
//
PlayerStateDribble::PlayerStateDribble(Player &in_player)
    : PlayerState(in_player) {
  name = "Dribble";
}
//
//
//
void PlayerStateDribble::start() {
  player.ball_under_control = true;
  already_kicked = false;
  player.movable.speed = dribble_speeds[player.speed];
}
//
//
//
void PlayerStateDribble::close_control() {
  already_kicked = false;
  // edge of feet circle in direction of movement
  Vector3 ball_position{player.feet.getCenter()};
  Vector3 offset = player.facing.toVector() *
                   (player.feet.getRadius() +
                    player.getMatch().getBall().collidable.getRadius());
  ball_position += offset * 1.f;

  // put the ball there
  player.getMatch().getBall().movable.place(ball_position);
}
//
//
//
void PlayerStateDribble::step() {
  PlayerState::step();

  // check for changed direction (close control)
  Compass old_direction = player.facing;
  Vector3 dir = player.movable.getVelocity();
  player.facing.fromVector(dir);
  if (old_direction.direction != player.facing.direction) {
    close_control();
  } else {
    // check for collision with ball
    if (Collider::collides(player.feet,
                           player.getMatch().getBall().collidable)) {
      if (!already_kicked) {
        kick();
      }
    } else {
      already_kicked = false;
    }
  }

  player.player_sprite.setAnimation(PlayerAnimationType::Run,
                                    player.facing.direction);
}
//
//
//
void PlayerStateDribble::stop() {}
//
//
//
bool PlayerStateDribble::stateOver() {
  // check if ball is outside control range
  if (!player.ballInControlRange()) {
    next_state = player_state::Run;
    player.ball_under_control = false;
    return true;
  }
  // or if we stopped moving
  if (Math::equal(player.movable.getVelocityMag(true), 0)) {
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
  auto f= player.movable.getVelocityMag(true);
  f++;
  Vector3 kick_force = Compass(player.facing).toVector();
  kick_force.normalise2d();
  kick_force *= force;
  player.getMatch().getBall().kick(kick_force);
}
