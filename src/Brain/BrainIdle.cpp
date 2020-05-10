// ---------------------------------------------------------------------------
//
// Brain State Idle
//
// ---------------------------------------------------------------------------
#include "BrainIdle.h"

#include "Brain.hpp"
namespace Senseless {
BrainIdle::BrainIdle(Brain &in_brain): BrainState(in_brain)  {
    name = "Idle";
}

void BrainIdle::start(){
    brain.locomotion.stand();
}

void BrainIdle::step(){

}

void BrainIdle::stop(){

}

bool BrainIdle::stateOver(){
    return false;
}

}  // namespace Senseless
