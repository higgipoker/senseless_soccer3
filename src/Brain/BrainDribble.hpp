#pragma once
#include <iostream>

#include "BrainState.hpp"
#include "Engine/Compass.hpp"
#include "Engine/Vector.hpp"
namespace Senseless {
class Brain;
//
//
//
class DribblePattern {
 public:
  virtual Compass nextDirection(Compass in_current_dir) = 0;
  virtual bool changeDirection() = 0;

 protected:
  int count = 0;
};
//
//
//
class DribblePatternRandom : public DribblePattern {
 public:
  //
  //
  //
  Compass nextDirection(Compass in_current_dir) override {
    Vector3 v = in_current_dir.toVector();
    v.rotate(static_cast<float>(rand() % 2 == 1 ? 45 : -45));
    Compass dir(v);
    return dir;
  }
  //
  //
  //
  bool changeDirection() override {
    static const int min = 60;
    if (++count > min) {
      if (rand() % 100 > 45) {
        count = 0;
        return true;
      }
    }
    return false;
  }
};
//
//
//
class BrainDribble : public BrainState {
 public:
  BrainDribble(Brain &in_brain);
  void start() override;
  void step() override;
  void stop() override;
  bool stateOver() override;

 protected:
  DribblePatternRandom pattern_random;
  DribblePattern *pattern = nullptr;
  int dribble_ticks = 0;
  bool first_touch = true;
};
}  // namespace Senseless
