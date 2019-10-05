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
  Compass new_direction(player.movable.getVelocity());
  if (new_direction.direction != player.facing.direction) {
    player.close_control();
    std::cout << "PlayerStateDribble::step> close_control" << std::endl;
  } else {
    // check for collision with ball
    if (Collider::collides(player.feet, player.match->ball->collidable)) {
      float force = 1.F;
      player.match->ball->movable.resetVelocity();
      player.match->ball->movable.resetForces();
      player.match->ball->movable.applyForce(Compass(player.facing).toVector() *
                                             force);
      std::cout << "PlayerStateDribble::step> kick" << std::endl;
    }
  }
  player.facing = new_direction;
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
