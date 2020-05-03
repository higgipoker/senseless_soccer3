#include "BrainWait.hpp"

#include "Ball/Ball.hpp"
#include "Brain.hpp"
#include "Player/Player.hpp"
namespace Senseless {
//
//
//
BrainWait::BrainWait(Brain& in_brain) : BrainState(in_brain) {
  name = "Retrieve";
  next_state = brain_state::Support;
}
//
//
//
void BrainWait::start() {
  ticks = 0;
  brain.locomotion.stand();
}
//
//
//
void BrainWait::step() {}
//
//
//
void BrainWait::stop() {}
//
//
//
bool BrainWait::stateOver() { return ++ticks > 1000; }
}  // namespace Senseless
