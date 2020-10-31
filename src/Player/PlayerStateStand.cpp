#include "PlayerStateStand.hpp"

#include "Player.hpp"
namespace Senseless {
//
//
//
PlayerStateStand::PlayerStateStand(Player &in_player) : PlayerState(in_player) { name = "Stand"; }
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
  player.player_sprite.setPlayerAnimation(PlayerAnimationType::Stand, player.facing.direction);
}
//
//
//
void PlayerStateStand::stop() {}
//
//
//
bool PlayerStateStand::stateOver() {
  return Math::greater_than(Vector::magnitude2d(player.movable.velocity), 0);
}
}  // namespace Senseless
