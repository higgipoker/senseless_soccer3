#include "Brain.hpp"

#include <iostream>

#include "Player/Player.hpp"
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
      current_state(&idle_state) {}
//
//
//
void Brain::update() {
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
