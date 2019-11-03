#pragma once

#include "Engine/Vector.hpp"
#include "Locomotion/Head.hpp"
#include "Locomotion/Pursue.hpp"
#include "Locomotion/Seek.hpp"
#include "Locomotion/Stand.hpp"

class Player;
/**
 * @brief The LocomotionManager class
 */
class LocomotionManager {
 public:
  //
  //
  //
  LocomotionManager(Player &in_player);
  //
  //
  //
  void seek(const Engine::Vector3 in_target);
  //
  //
  //
  void head(const Engine::Vector3 in_target);
  //
  //
  //
  void pursue(Engine::Movable &in_target);
  //
  //
  //
  void stand();
  //
  //
  //
  void update();

 private:
  Seek seek_locomotion;
  Head head_locomotion;
  Pursue pursue_locomotion;
  Stand stand_locomotion;
  Locomotion *current_locomotion = nullptr;
};
