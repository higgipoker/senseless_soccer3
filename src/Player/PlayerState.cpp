#include "PlayerState.hpp"
//
#include "Player.hpp"

using namespace Engine;
//
//
//
PlayerState::PlayerState(Player &in_player) : player(in_player) {}
//
//
//
PlayerState::~PlayerState() {}
//
//
//
void PlayerState::step() {
  // normalizes for diagonals
  if (Math::greater_than(player.movable.getVelocityMag(), 0)) {
    player.movable.normalizeVelocity(true);
  }

  player.feet.setPosition(player.movable.getX() - player.feet.getRadius(),
                          player.movable.getY() - player.feet.getRadius());
  player.control.setPosition(
      player.movable.getX() - player.control.getRadius(),
      player.movable.getY() - player.control.getRadius());
}
//
//
//
player_state PlayerState::nextState() { return next_state; }
