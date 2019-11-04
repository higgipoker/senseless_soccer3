#include "BrainPass.hpp"

#include "Brain.hpp"

#include "Player/Player.hpp"
#include "Team/Team.hpp"
static const int PASS_TICKS = 0;
//
//
//
BrainPass::BrainPass(Brain& in_brain) : BrainState(in_brain) {
  name = "Pass";
  next_state = brain_state::Wait;
}
//
//
//
void BrainPass::start() {
  ticks = 0;
  receiver = brain.player.my_team->key_players.closest_to_ball;
}
//
//
//
void BrainPass::step() {
  if (++ticks > PASS_TICKS) {
    brain.player.shortPass(*receiver);
    receiver = nullptr;
  }
}
//
//
//
void BrainPass::stop() {}
//
//
//
bool BrainPass::stateOver() {
  if (receiver) return false;
  return true;
}
//
//
//
void BrainPass::select_receiver() {}
