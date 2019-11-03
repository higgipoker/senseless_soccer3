#pragma once
#include "BrainState.hpp"
class Brain;
/**
 * @brief The Retrieve class
 */
class BrainWait : public BrainState {
 public:
  /**
   * @brief Retrieve
   */
  BrainWait(Brain &in_brain);
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
  int ticks = 0;
};
