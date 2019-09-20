#pragma once
class Player;

/**
 * @brief The player_state enum
 */
enum class player_state { Stand, Run };

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
  virtual void step() = 0;
  /**
   * @brief end
   */
  virtual void end() = 0;
  /**
   * @brief stateOver
   * @return
   */
  virtual bool stateOver() = 0;
  /**
   * @brief changeToNextState
   */
  void changeToNextState();

 protected:
  /// context for state  machine pattern
  Player &player;

  /// next state
  player_state next_state = player_state::Stand;
};
