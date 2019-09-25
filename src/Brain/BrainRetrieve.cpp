#include "BrainRetrieve.hpp"

#include "Ball/Ball.hpp"
#include "Brain.hpp"
#include "Match/Match.hpp"
#include "Player/Player.hpp"
//
//
//
BrainRetrieve::BrainRetrieve(Brain& in_brain) : BrainState(in_brain) {
  name = "Retrieve";
  next_state = brain_state::Dribble;
}
//
//
//
void BrainRetrieve::start() {
  brain.locomotion.pursue(brain.player.match->ball->movable);
}
//
//
//
void BrainRetrieve::step() {}
//
//
//
void BrainRetrieve::stop() {}
//
//
//
bool BrainRetrieve::stateOver() { return brain.player.ball_under_control; }
