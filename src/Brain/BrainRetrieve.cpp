#include "BrainRetrieve.hpp"

#include "Brain.hpp"
#include "Match/Match.hpp"
#include "Player/Player.hpp"
#include "Ball/Ball.hpp"
//
//
//
BrainRetrieve::BrainRetrieve(Brain& in_brain) : BrainState(in_brain) {name = "Retrieve";}
//
//
//
void BrainRetrieve::start() {
  brain.locomotion.pursue_til_caught(brain.player.match->ball->movable, 5);
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
bool BrainRetrieve::stateOver() { return false; }
