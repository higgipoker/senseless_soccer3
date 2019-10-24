#include "PlayerStateStand.hpp"

#include "Player.hpp"
using namespace Engine;
//
//
//
PlayerStateStand::PlayerStateStand(Player &in_player) : PlayerState(in_player) {
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
  player.player_sprite.setPlayerAnimation(PlayerAnimationType::Stand,
                                          player.facing.direction);
}
//
//
//
void PlayerStateStand::stop() {}
//
//
//
bool PlayerStateStand::stateOver() {
  return Math::greater_than(player.movable.getVelocityMag(true), 0);
}
