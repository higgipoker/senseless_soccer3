// ---------------------------------------------------------------------------
//
// Brain State Idle
//
// ---------------------------------------------------------------------------
#pragma once
#include "BrainState.hpp"
namespace Senseless {
class BrainIdle : public BrainState {
   public:
    BrainIdle(Brain &in_brain);

    void start      () override;
    void step       () override;
    void stop       () override;
    bool stateOver  () override;
};
}  // namespace Senseless
