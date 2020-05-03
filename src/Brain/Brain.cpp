// ---------------------------------------------------------------------------
//
// Brain
//
// ---------------------------------------------------------------------------
#include "Brain.hpp"

#include "Match/Match.hpp"
#include "Pitch/Pitch.hpp"
#include "Player/Player.hpp"
#include "Team/Team.hpp"

#include <iostream>

namespace Senseless {
//
//
//
Brain::Brain(Player &in_player)
    : locomotion(in_player),
      player(in_player),
      idle_state(*this),
      cover_state(*this),
      retrieve_state(*this),
      dribble_state(*this),
      pass_state(*this),
      support_state(*this),
      wait_state(*this),
      current_state(&idle_state) {
}
//
//
//
void Brain::initEnvironment(Match *in_match,
                            Team * in_my_team,
                            Team * in_other_team,
                            Pitch *in_pitch) {
    env.match      = in_match;
    env.my_team    = in_my_team;
    env.other_team = in_other_team;
    env.pitch      = in_pitch;
}
//
//
//
void Brain::think() {
    // state machine
    current_state->step();
    if (current_state->stateOver()) {
        current_state->changeToNextState();
    }
    locomotion.update();
}
//
//
//
void Brain::changeState(const brain_state in_state) {
    state = in_state;
    current_state->stop();

    switch (in_state) {
        case brain_state::Idle:
            current_state = &idle_state;
            break;
        case brain_state::Cover:
            current_state = &cover_state;
            break;
        case brain_state::Retrieve:
            current_state = &retrieve_state;
            break;
        case brain_state::Dribble:
            current_state = &dribble_state;
            break;
        case brain_state::Pass:
            current_state = &pass_state;
            break;
        case brain_state::Support:
            current_state = &support_state;
            break;
        case brain_state::Wait:
            current_state = &wait_state;
            break;
    }
    current_state->start();
}
}  // namespace Senseless
