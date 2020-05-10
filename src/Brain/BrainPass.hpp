#pragma once
#include "BrainState.hpp"
//
namespace Senseless {
class Player;
// ***************************************************************************
// *                                                                         *
// * BrainPass                                                               *
// *                                                                         *
// ***************************************************************************
class BrainPass : public BrainState {
    public:
                BrainPass   (Brain &in_brain);
    virtual void start        () override;
    virtual void step         () override;
    virtual void stop         () override;
    virtual bool stateOver    () override;

    private:
    Player*   receiver    = nullptr;
    int       ticks       = 0;
    void select_receiver();

};
}  // namespace Senseless
