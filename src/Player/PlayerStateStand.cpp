#include "PlayerStateStand.hpp"

#include "Player.hpp"
using namespace Engine;
//
//
//
PlayerStateStand::PlayerStateStand(Player &in_player)
    : PlayerState(in_player) {
  name = "Stand";
}
//
//
//
void PlayerStateStand::start() { next_state = player_state::Run; }
//
//
//
void PlayerStateStand::step() {
  PlayerState::step();

  player.face_ball();
  player.player_sprite.setAnimation(PlayerAnimationType::Stand, player.facing.direction);
}
//
//
//
void PlayerStateStand::stop() {}
//
//
//
bool PlayerStateStand::stateOver() {
  return Math::greater_than(player.movable.velocity.magnitude2d(), 0);
}
