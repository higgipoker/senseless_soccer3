#include "PlayerStateRun.hpp"

#include "Match/Match.hpp"
#include "Player.hpp"

#include "Engine/Collider.hpp"
#include "Engine/Compass.hpp"
using namespace Engine;
//
//
//
PlayerStateRun::PlayerStateRun(Player &in_player) : PlayerState(in_player) {
  next_state = player_state::Stand;
  name = "Run";
}
//
//
//
void PlayerStateRun::start() {

}
//
//
//
void PlayerStateRun::step() {
  Engine::Compass direction(player.movable.velocity);
  player.player_sprite.setAnimation(PlayerAnimationType::Run,
                                    direction.direction);
}
//
//
//
void PlayerStateRun::stop() {}
//
//
//
bool PlayerStateRun::stateOver() {
  // stopped moving
  if (Floats::equal(player.movable.velocity.magnitude2d(), 0)) {
    next_state = player_state::Stand;
    return true;
  }
  // check if we need to transitio to dribble
  if (Collider::collides(player.feet, player.match->ball->collidable)) {
    next_state = player_state::Dribble;
    return true;
  }
  return false;
}
