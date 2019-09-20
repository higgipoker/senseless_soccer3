#include "PlayerStateStand.hpp"

#include "Player.hpp"
using namespace Engine;
//
//
//
PlayerStateStand::PlayerStateStand(Player &in_player)
    : PlayerState(in_player) {}
//
//
//
void PlayerStateStand::start() { next_state = player_state::Run; }
//
//
//
void PlayerStateStand::step() {
  player.face_ball();
  player.player_sprite->setAnimation(PlayerAnimationType::Stand, player.facing);
}
//
//
//
void PlayerStateStand::end() {}
//
//
//
bool PlayerStateStand::stateOver() {
  return Floats::greater_than(player.movable->velocity.magnitude2d(), 0);
}
