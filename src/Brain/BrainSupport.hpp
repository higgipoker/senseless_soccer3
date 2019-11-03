#pragma once
#include "BrainState.hpp"

#include <SFML/Graphics/CircleShape.hpp>
class Player;
//
//
//
class BrainSupport : public BrainState {
 public:
  //
  //
  //
  BrainSupport(Brain& in_brain);
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
  Player* player_in_possession;
  int ticks_since_change = 0;
  sf::CircleShape radius;
  //
  //
  //
  void change_direction();
};
