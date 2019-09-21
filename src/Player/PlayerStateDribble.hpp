#pragma once
#include "PlayerState.hpp"
class Player;
/**
 * @brief The PlayerStateDribble class
 */
class PlayerStateDribble : public PlayerState {
 public:
  /**
   * @brief PlayerStateDribble
   */
  PlayerStateDribble(Player &in_player);
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
