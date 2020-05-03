#include "BrainDribble.hpp"

#include "Ball/Ball.hpp"
#include "Brain.hpp"
#include "Player/Player.hpp"
namespace Senseless {
static const int DRIBBLE_TIME = 100;
//
//
//
BrainDribble::BrainDribble(Brain& in_brain) : BrainState(in_brain), pattern(&pattern_random) {
  name = "Dribble";
  next_state = brain_state::Wait;
}
//
//
//
void BrainDribble::start() {
  brain.player.current_speed = dribble_speeds[brain.player.speed];
  dribble_ticks = 0;
  brain.locomotion.head(brain.player.getDirection().toVector());
}
//
//
//
void BrainDribble::step() {
  if (++dribble_ticks > DRIBBLE_TIME && !brain.player.short_pass_candidates.empty()) {
    brain.changeState(brain_state::Pass);

  } else if (pattern->changeDirection()) {
    brain.locomotion.head(pattern->nextDirection(brain.player.getDirection()).toVector());
  }
}
//
//
//
void BrainDribble::stop() { brain.locomotion.stand(); }
//
//
//
bool BrainDribble::stateOver() {
  if (brain.player.ballInControlRange()) return false;
  return true;
}
}  // namespace Senseless
