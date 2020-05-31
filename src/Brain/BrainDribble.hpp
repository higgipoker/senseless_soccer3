#pragma once
#include <iostream>

#include "BrainState.hpp"
#include "Engine/Compass.hpp"
#include "Engine/Vector.hpp"
#include "DribblePattern.hpp"
namespace Senseless {
class Brain;
// ***************************************************************************
// *                                                                         *
// * BrainDribble                                                            *
// *                                                                         *
// ***************************************************************************
class BrainDribble : public BrainState {
 public:
        BrainDribble(Brain &in_brain);
    void  start       () override;
    void  step        () override;
    void  stop        () override;
    bool  stateOver   () override;

    protected:
    DribblePatternRandom  pattern_random;
    DribblePattern*       pattern = nullptr;
    int                   dribble_ticks = 0;
    bool                  first_touch = true;

    void turn();
    bool is_turning();
    bool turning = false;
    bool waiting_for_reenter_bounds = false;
    Direction turn_target_direction = Direction::North;    
};
}  // namespace Senseless
