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
  name = "Retrieve";
}
//
//
//
void BrainDribble::start() {
  brain.locomotion.head(pattern->nextDirection());
}
//
//
//
void BrainDribble::step() {
  if(pattern->changeDirection()){
    brain.locomotion.head(pattern->nextDirection());
  }
}
//
//
//
void BrainDribble::stop() {}
//
//
//
bool BrainDribble::stateOver() { return false; }
