#include "BrainState.hpp"

#include "Brain.hpp"

//
//
//
BrainState::BrainState(Brain& in_brain) : brain(in_brain) {}
//
//
//
BrainState::~BrainState() {}
//
//
//
void BrainState::changeToNextState() { brain.changeState(next_state); }
