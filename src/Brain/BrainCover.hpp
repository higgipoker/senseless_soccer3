#pragma once
#include "BrainState.hpp"
//
#include <SFML/Graphics/CircleShape.hpp>
#include "Engine/Vector.hpp"
class Player;
//
//
//
class BrainCover : public BrainState {
   public:
    //
    //
    //
    BrainCover(Brain& in_brain);
    //
    //
    //
    virtual void start() override;
    //
    //
    //
    virtual void step() override;
    //
    //
    //
    virtual void stop() override;
    //
    //
    //
    virtual bool stateOver() override;

   private:
    //
    //
    //
    void change_direction();
    //
    Engine::Vector3 last_target;
};