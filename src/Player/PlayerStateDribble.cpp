#include "PlayerStateDribble.hpp"

#include "Match/Match.hpp"
#include "Player.hpp"

#include "Engine/Collider.hpp"
#include "Engine/Compass.hpp"
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
  Engine::Compass direction(player.movable.velocity);
  player.player_sprite.setAnimation(PlayerAnimationType::Run,
                                    direction.direction);
}
//
//
//
void PlayerStateDribble::step() {
  // check for collision with ball
  if (Collider::collides(player.feet, player.match->ball->collidable)) {
    float force = 1.F;
    player.match->ball->movable.velocity.reset();
    player.match->ball->movable.force =
        Compass(player.facing).toVector() * force;
    std::cout << "kick" << std::endl;
  }
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
  if (Floats::equal(player.movable.velocity.magnitude2d(), 0)) {
    next_state = player_state::Stand;
    return true;
  }

  return false;
}
