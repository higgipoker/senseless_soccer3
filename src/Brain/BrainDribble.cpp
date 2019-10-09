#include "BrainDribble.hpp"

#include "Ball/Ball.hpp"
#include "Brain.hpp"
#include "Match/Match.hpp"
#include "Player/Player.hpp"
//
//
//
BrainDribble::BrainDribble(Brain& in_brain)
    : BrainState(in_brain), pattern(&pattern_random) {
  name = "Dribble";
  next_state = brain_state::Idle;
}
//
//
//
void BrainDribble::start() {
  brain.locomotion.head(brain.player.direction().toVector());
}
//
//
//
void BrainDribble::step() {
  if(pattern->changeDirection()){
    brain.locomotion.head(pattern->nextDirection(brain.player.direction()));
  }
}
//
//
//
void BrainDribble::stop() {}
//
//
//
bool BrainDribble::stateOver() { return !brain.player.ballInControlRange(); }
