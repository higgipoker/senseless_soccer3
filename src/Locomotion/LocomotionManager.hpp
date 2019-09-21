#pragma once

#include "Locomotion/Seek.hpp"
#include "Locomotion/Head.hpp"
#include "Locomotion/Pursue.hpp"
#include "Engine/Vector.hpp"

class Player;
/**
 * @brief The LocomotionManager class
 */
class LocomotionManager
{
public:
  /**
   * @brief LocomotionManager
   */
  LocomotionManager(Player &in_player);
  /**
   * @brief seek
   * @param in_target
   */
  void seek(const Engine::Vector3 in_target);
  /**
   * @brief head
   * @param in_target
   */
  void head(const Engine::Vector3 in_target);
  /**
   * @brief pursue
   * @param in_target
   */
  void pursue(Engine::Movable &in_target);
  /**
   * @brief pursue_til_caught
   * @param in_target
   */
  void pursue_til_caught(Engine::Movable &in_target, float in_range);
  /**
   * @brief update
   */
  void update();

private:
  Seek seek_locomotion;
  Head head_locomotion;
  Pursue pursue_locomotion;
  PursueTilCaught pursue_til_caught_locomotion;
  Locomotion *current_locomotion = nullptr;
};
