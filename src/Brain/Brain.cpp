#include "Brain.hpp"

#include "Player/Player.hpp"

#include <iostream>
//
//
//
Brain::Brain(Player &in_player)
    : locomotion(in_player),
      player(in_player),
      idle_state(*this),
      retrieve_state(*this),
      dribble_state(*this),
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
    case brain_state::Retrieve:
      current_state = &retrieve_state;
      break;
    case brain_state::Dribble:
      current_state = &dribble_state;
      break;
  }
  current_state->start();
  std::cout << "Brain::changeState> " << current_state->name << std::endl;
}
