#pragma once
#include <iostream>

#include "BrainState.hpp"
#include "Engine/Compass.hpp"
#include "Engine/Vector.hpp"
#include "DribblePattern.hpp"
namespace Senseless {
class Brain;

enum class DribbleObjective {
    Cross,
    Shot,
    Evade,
    GainGround,
    WasteTime,
};

// ***************************************************************************
// *                                                                         *
// * BrainDribble                                                            *
// *                                                                         *
// ***************************************************************************
class BrainDribble : public BrainState {
   public:
    BrainDribble(Brain& in_brain);
    void init(const DribbleObjective obj);
    void start() override;
    void step() override;
    void stop() override;
    bool stateOver() override;

   protected:
    DribbleObjective     objective = DribbleObjective::WasteTime;
    DribblePatternRandom pattern_random;
    DribblePattern*      pattern                    = nullptr;
    int                  dribble_ticks              = 0;
    bool                 first_touch                = true;
    bool                 turning                    = false;
    bool                 waiting_for_reenter_bounds = false;
    Direction            turn_target_direction      = Direction::North;
    float                rotate_direction = 0;
    void                 turn();
    bool                 is_turning();
    int ticks_since_turn = 0;
};
}  // namespace Senseless
