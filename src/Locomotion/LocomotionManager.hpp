#pragma once

#include "Engine/Vector.hpp"
#include "Locomotion/Head.hpp"
#include "Locomotion/Pursue.hpp"
#include "Locomotion/Seek.hpp"
#include "Locomotion/Stand.hpp"
namespace Senseless {
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
  void seek(const Vector3 in_target);
  //
  //
  //
  void head(const Vector3 in_target);
  //
  //
  //
  void pursue(Movable &in_target);
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

}  // namespace Senseless
