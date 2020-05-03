#pragma once
#include "BrainState.hpp"
//
namespace Senseless {
class Player;
//
//
//
class BrainPass : public BrainState {
 public:
  //
  //
  //
  BrainPass(Brain &in_brain);
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
  Player *receiver = nullptr;
  //
  //
  //
  void select_receiver();
  int ticks = 0;
};
}  // namespace Senseless
