#pragma once
#include "Engine/Vector.hpp"

class Player;
/**
 * @brief The Locomotion class
 */
class Locomotion {
 public:
  /**
   * @brief Locomotion
   */
  Locomotion(Player &in_player);
  /**
   * @brief ~Locomotion
   */
  virtual ~Locomotion() = default;
  /**
   * @brief start
   */
  virtual void start() = 0;
  /**
   * @brief step
   */
  virtual void step() = 0;
  /**
   * @brief end
   */
  virtual void stop() = 0;
  /**
   * @brief fiished
   * @return
   */
  virtual bool finished() = 0;

 protected:
  /// entity to manipulate
  Player &player;
  //
  //
  //
  void stay_in_pitch();
};
