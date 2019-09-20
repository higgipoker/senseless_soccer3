#pragma once
#include "PlayerState.hpp"
class Player;
/**
 * @brief The PlayerStateStand class
 */
class PlayerStateStand : public PlayerState {
 public:
  /**
   * @brief PlayerStateStand
   */
  PlayerStateStand(Player &in_player);
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
  void end() override;
  /**
   * @brief stateOver
   * @return
   */
  bool stateOver() override;

};
