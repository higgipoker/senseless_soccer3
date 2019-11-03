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
  std::cout << "start " << name << std::endl;
  brain.locomotion.pursue(brain.player.getMatch().getBall().movable);
}
//
//
//
void BrainRetrieve::step() {}
//
//
//
void BrainRetrieve::stop() {std::cout << "stop " << name << std::endl;}
//
//
//
bool BrainRetrieve::stateOver() { return brain.player.ball_under_control; }
