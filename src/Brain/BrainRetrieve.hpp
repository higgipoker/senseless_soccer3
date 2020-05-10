#pragma once
#include "BrainState.hpp"
namespace Senseless {
class Brain;
// ***************************************************************************
// *                                                                         *
// * BrainRetrieve                                                           *
// *                                                                         *
// ***************************************************************************
class BrainRetrieve : public BrainState {
    public:
    BrainRetrieve     (Brain &in_brain);
    void start        ()                  override;
    void step         ()                  override;
    void stop         ()                  override;
    bool stateOver    ()                  override;
};
}  // namespace Senseless
