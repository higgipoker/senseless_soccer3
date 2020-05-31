#include "BrainRetrieve.hpp"
//
#include "Brain.hpp"
//
#include "Ball/Ball.hpp"
#include "Match/Match.hpp"
#include "Player/Player.hpp"
//
//
//
namespace Senseless {
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
    brain.locomotion.pursue(brain.player.match->getBall().movable);
}
//
//
//
void BrainRetrieve::step() {

}
//
//
//
void BrainRetrieve::stop() {

}
//
//
//
bool BrainRetrieve::stateOver() {
    return brain.player.ball_under_control;
}
}  // namespace Senseless
