#pragma once
#include "BrainState.hpp"
namespace Senseless {
class Brain;
/**
 * @brief The Retrieve class
 */
class BrainRetrieve : public BrainState {
 public:
  /**
   * @brief Retrieve
   */
  BrainRetrieve(Brain &in_brain);
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
};
}  // namespace Senseless
