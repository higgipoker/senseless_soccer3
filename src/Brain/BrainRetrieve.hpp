#pragma once
#include "BrainState.hpp"
namespace Senseless {
class Brain;
/////////////////////////////////////////
//
// Behaviour:       move towards the ball
// End condition:   ball is under control
//
/////////////////////////////////////////
class BrainRetrieve : public BrainState {
 public:
  BrainRetrieve     (Brain &in_brain);
  void start        ()                  override;
  void step         ()                  override;
  void stop         ()                  override;
  bool stateOver    ()                  override;
};
}  // namespace Senseless
