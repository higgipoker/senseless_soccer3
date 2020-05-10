#pragma once
#include "BrainState.hpp"
namespace Senseless {
class Brain;
// ***************************************************************************
// *                                                                         *
// * BrainWait                                                               *
// *                                                                         *
// ***************************************************************************
class BrainWait : public BrainState {
    public:
        BrainWait   (Brain &in_brain);
    void  start       () override;
    void  step        () override;
    void  stop        () override;
    bool  stateOver   () override;

    protected:
    int ticks = 0;
};
}  // namespace Senseless
