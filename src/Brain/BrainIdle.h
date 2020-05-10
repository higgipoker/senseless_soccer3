#pragma once
#include "BrainState.hpp"
namespace Senseless {
// ***************************************************************************
// *                                                                         *
// * BrainIdle                                                               *
// *                                                                         *
// ***************************************************************************
class BrainIdle : public BrainState {
    public:
    BrainIdle(Brain &in_brain);

    void start      () override;
    void step       () override;
    void stop       () override;
    bool stateOver  () override;
};
}  // namespace Senseless
