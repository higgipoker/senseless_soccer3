#pragma once
#include "PlayerState.hpp"
namespace Senseless {
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

 protected:
  // kick once until the ball leaves the foot!
  bool already_kicked = false;
  //
  //
  //
  void close_control();
  //
  //
  //
  void kick();
};
}  // namespace Senseless
