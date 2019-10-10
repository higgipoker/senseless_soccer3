#include "PlayerStateDribble.hpp"

#include "Match/Match.hpp"
#include "Player.hpp"

#include "Engine/Collider.hpp"
#include "Engine/Compass.hpp"

#include <iostream>
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
void PlayerStateDribble::start() { player.ball_under_control = true; }
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
    player.close_control();
    std::cout << "PlayerStateDribble::step> close_control" << std::endl;
  } else {
    // check for collision with ball
    if (Collider::collides(player.feet, player.match->ball->collidable)) {
      constexpr float force = 0.1F; // tmp
      player.match->ball->movable.resetForces();
      Vector3 kick_force = Compass(player.facing).toVector();
      kick_force.normalise2d();
      player.match->ball->movable.applyForce(kick_force * force);
      std::cout << "PlayerStateDribble::step> kick" << std::endl;
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
  if (!Collider::contains(player.control, player.match->ball->collidable)) {
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
