#include "PlayerStateRun.hpp"

#include "Engine/Collider.hpp"
#include "Engine/Compass.hpp"
#include "Match/Match.hpp"
#include "Player.hpp"
namespace Senseless {
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
void PlayerStateRun::start() { player.current_speed = run_speeds[player.speed]; }
//
//
//
void PlayerStateRun::step() {
  PlayerState::step();

  Compass direction(player.movable.velocity);
  player.player_sprite.setPlayerAnimation(PlayerAnimationType::Run, direction.direction);
}
//
//
//
void PlayerStateRun::stop() {}
//
//
//
bool PlayerStateRun::stateOver() {
  // go to dribble
  if (player.ballInControlRange()) {
    next_state = player_state::Dribble;
    return true;
  }
  // go to stand
  if (Math::equal(Vector::magnitude2d(player.movable.velocity), 0)) {
    next_state = player_state::Stand;
    return true;
  }
  return false;
}
}  // namespace Senseless
