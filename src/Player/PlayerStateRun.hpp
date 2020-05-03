#pragma once
#include "PlayerState.hpp"
namespace Senseless {
class Player;
/**
 * @brief The PlayerStateRun class
 */
class PlayerStateRun : public PlayerState {
 public:
  /**
   * @brief PlayerStateRun
   */
  PlayerStateRun(Player &in_player);
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
