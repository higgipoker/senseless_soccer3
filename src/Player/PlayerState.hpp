#pragma once
#include <string>
class Player;

/**
 * @brief The player_state enum
 */
enum class player_state { Stand, Run, Dribble };

/**
 * @brief The PlayerState class
 */
class PlayerState {
 public:
  /**
   * @brief PlayerState
   */
  PlayerState(Player &in_player);
  /**
   * @brief ~PlayerState
   */
  virtual ~PlayerState();
  /**
   * @brief start
   */
  virtual void start() = 0;
  /**
   * @brief update
   */
  virtual void step();
  /**
   * @brief end
   */
  virtual void stop() = 0;
  /**
   * @brief stateOver
   * @return
   */
  virtual bool stateOver() = 0;
  /**
   * @brief changeToNextState
   */
  player_state nextState();

  /// degug
  std::string name;

 protected:
  /// context for state  machine pattern
  Player &player;

  /// next state
  player_state next_state = player_state::Stand;
};
