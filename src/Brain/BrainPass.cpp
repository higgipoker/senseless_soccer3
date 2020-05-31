#include "BrainPass.hpp"

#include "Brain.hpp"
#include "Player/Player.hpp"
#include "Team/Team.hpp"
namespace Senseless {
static const int PASS_TICKS = 0;
//
//
//
BrainPass::BrainPass(Brain& in_brain) : BrainState(in_brain) {
    name       = "Pass";
    next_state = brain_state::Wait;
}
//
//
//
void BrainPass::start() {
    ticks = 0;
    if (!brain.player.short_pass_candidates.empty()) {
        receiver = brain.player.short_pass_candidates[0];
    }
}
//
//
//
void BrainPass::step() {
    if (receiver) {
        if (++ticks > PASS_TICKS) {
            brain.player.shortPass(*receiver);
            receiver = nullptr;
        }
    }
}
//
//
//
void BrainPass::stop() {
}
//
//
//
bool BrainPass::stateOver() {
    if (receiver)
        return false;
    return true;
}
//
//
//
void BrainPass::select_receiver() {
}
}  // namespace Senseless
