#include "PlayerStateDribble.hpp"

#include "Player.hpp"

#include "Engine/Compass.hpp"
//
//
//
PlayerStateDribble::PlayerStateDribble(Player &in_player) : PlayerState(in_player) {}
//
//
//
void PlayerStateDribble::start() {
  Engine::Compass direction(player.movable->velocity);
  player.player_sprite->setAnimation(PlayerAnimationType::Run, direction.direction);
}
//
//
//
void PlayerStateDribble::step() {}
//
//
//
void PlayerStateDribble::stop() {}
//
//
//
bool PlayerStateDribble::stateOver() { return false; }
