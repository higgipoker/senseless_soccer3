#include "PlayerState.hpp"
//
#include "Player.hpp"
//
//
//
PlayerState::PlayerState(Player &in_player)
  : player(in_player) {
}
//
//
//
PlayerState::~PlayerState() {
}
//
//
//
void PlayerState::step() {
  // normalizes for diagonals
  if (Engine::Math::greater_than(player.movable.velocity.magnitude(), 0)) {
    player.movable.velocity.normalise2d();
  }

  player.feet.setPosition(player.movable.position.x - player.feet.getRadius(),
                          player.movable.position.y - player.feet.getRadius());
  player.control.setPosition(player.movable.position.x - player.control.getRadius(),
                             player.movable.position.y - player.control.getRadius());
}
//
//
//
player_state PlayerState::nextState() {
  return next_state;
}
