#include "LocomotionManager.hpp"

#include "Engine/Entity.hpp"

#include "Player/Player.hpp"

using namespace Engine;
//
//
//
LocomotionManager::LocomotionManager(Player &in_player)
    : seek_locomotion(in_player),
      head_locomotion(in_player),
      pursue_locomotion(in_player) {}

//
//
//
void LocomotionManager::seek(const Vector3 in_target) {
  if (current_locomotion) {
    current_locomotion->stop();
  }
  seek_locomotion.init(in_target);
  current_locomotion = &seek_locomotion;
  current_locomotion->start();
}
//
//
//
void LocomotionManager::head(const Vector3 in_target) {
  if (current_locomotion) {
    current_locomotion->stop();
  }
  head_locomotion.init(in_target);
  current_locomotion = &head_locomotion;
  current_locomotion->start();
}
//
//
//
void LocomotionManager::pursue(Movable &in_target) {
  if (current_locomotion) {
    current_locomotion->stop();
  }
  pursue_locomotion.init(in_target);
  current_locomotion = &pursue_locomotion;
  current_locomotion->start();
}
//
//
//
void LocomotionManager::update() {
  if (current_locomotion != nullptr) {
    current_locomotion->step();
    if (current_locomotion->finished()) {
      current_locomotion->stop();
      current_locomotion = nullptr;
    }
  }
}
