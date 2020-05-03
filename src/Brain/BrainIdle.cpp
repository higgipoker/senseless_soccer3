// ---------------------------------------------------------------------------
//
// Brain State Idle
//
// ---------------------------------------------------------------------------
#include "BrainIdle.h"
namespace Senseless {
BrainIdle::BrainIdle(Brain &in_brain): BrainState(in_brain)  {
    name = "Idle";
}

void BrainIdle::start(){

}

void BrainIdle::step(){

}

void BrainIdle::stop(){

}

bool BrainIdle::stateOver(){
    return false;
}

}  // namespace Senseless
