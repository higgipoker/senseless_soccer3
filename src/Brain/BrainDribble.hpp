#pragma once
#include "BrainState.hpp"
#include "Engine/Compass.hpp"
#include "Engine/Vector.hpp"

#include <iostream>

class Brain;
//
//
//
class DribblePattern {
 public:
  //
  //
  //
  virtual Engine::Vector3 nextDirection(Engine::Compass in_current_dir) = 0;
  //
  //
  //
  virtual bool changeDirection() = 0;

 protected:
  int counter = 0;
};
//
//
//
class DribblePatternRandom : public DribblePattern {
 public:
  //
  //
  //
  Engine::Vector3 nextDirection(Engine::Compass in_current_dir) override {
    counter = 0;
    Engine::Vector3 dir = in_current_dir.toVector();
    dir.rotate(rand() % 2 == 1 ? 45 : -45);
    return dir;
  }
  //
  //
  //
  bool changeDirection() override {
    return (++counter > ((rand() % 50) + 100));
  }
};
//
//
//
class BrainDribble : public BrainState {
 public:
  /**
   * @brief Retrieve
   */
  BrainDribble(Brain &in_brain);
  /**
   * @brief start
   */
  void start() override;
  /**
   * @brief update
   */
  void step() override;
  /**
   * @brief end
   */
  void stop() override;
  /**
   * @brief stateOver
   * @return
   */
  bool stateOver() override;

 protected:
  DribblePatternRandom pattern_random;
  DribblePattern *pattern = nullptr;
};
