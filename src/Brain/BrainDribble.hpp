#pragma once
#include "BrainState.hpp"
#include "Engine/Compass.hpp"
#include "Engine/Vector.hpp"

class Brain;

class DribblePattern {
 public:
  DribblePattern() = default;
  virtual ~DribblePattern() = default;

  virtual Engine::Vector3 nextDirection() = 0;
  virtual bool changeDirection() = 0;

 protected:
  int counter = 0;
};

class DribblePatternRandom : public DribblePattern {
 public:
  Engine::Vector3 nextDirection() override {
    counter = 0;
    Engine::Compass compass(static_cast<Engine::Direction>(rand() % 8));
    return compass.toVector();
  }

  bool changeDirection() override {
    return (++counter > ((rand() % 100) + 50));
  }
};

/**
 * @brief The Retrieve class
 */
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
