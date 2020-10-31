#pragma once
#include "BrainState.hpp"
//
#include <SFML/Graphics/CircleShape.hpp>

#include "Engine/Vector.hpp"
namespace Senseless {
class Player;
// ***************************************************************************
// *                                                                         *
// * BrainCover                                                              *
// *                                                                         *
// ***************************************************************************
class BrainCover : public BrainState {
    public:
       BrainCover   (Brain& in_brain);
    void start        ()          override;
    void step         ()          override;
    void stop         ()          override;
    bool stateOver    ()          override;

    private:
    void change_direction();
    bool should_close_down();
    sf::Vector3f last_target;
};
}  // namespace Senseless
