#include "brain.hpp"
//
//
//
void update_brain(Brain &brain, Player &player) {
  switch (brain.state) {
    case BrainState::Idle:
      break;
    case BrainState::Cover:
      break;
    case BrainState::Press:
      break;
    case BrainState::Tackle:
      break;
    case BrainState::Retrieve:
      break;
    case BrainState::Support:
      break;
    case BrainState::Dribble:
      break;
    case BrainState::Pass:
      break;
    case BrainState::Shoot:
      break;
  }
}
//
//
//
void change_brainstate(BrainState new_state) {}
//
//
//
void attach_brain(Brain &brain, Player &player) {
  // todo check if alrady exists
  brains.insert(std::make_pair(&player, &brain));
}
//
//
//
void update_brains() {
  for (auto &brain : brains) {
    update_brain(*brain.second, *brain.first);
  }
}
