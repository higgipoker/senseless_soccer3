#include "PlayerStateRun.hpp"

#include "Player.hpp"

#include "Engine/Compass.hpp"
//
//
//
PlayerStateRun::PlayerStateRun(Player &in_player) : PlayerState(in_player) {}
//
//
//
void PlayerStateRun::start() {
  Engine::Compass direction(player.movable->velocity);
  player.player_sprite->setAnimation(PlayerAnimationType::Run, direction.direction);
}
//
//
//
void PlayerStateRun::step() {}
//
//
//
void PlayerStateRun::end() {}
//
//
//
bool PlayerStateRun::stateOver() { return false; }
