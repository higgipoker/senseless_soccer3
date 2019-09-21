#include "PlayerStateRun.hpp"

#include "Player.hpp"

#include "Engine/Compass.hpp"
//
//
//
PlayerStateRun::PlayerStateRun(Player &in_player) : PlayerState(in_player) {
  next_state = player_state::Stand;
}
//
//
//
void PlayerStateRun::start() {
  Engine::Compass direction(player.movable->velocity);
  player.player_sprite->setAnimation(PlayerAnimationType::Run,
                                     direction.direction);
}
//
//
//
void PlayerStateRun::step() {}
//
//
//
void PlayerStateRun::stop() {}
//
//
//
bool PlayerStateRun::stateOver() {
  return Engine::Floats::equal(player.movable->velocity.magnitude2d(), 0);
}
