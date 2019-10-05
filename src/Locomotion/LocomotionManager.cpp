#include "LocomotionManager.hpp"

#include "Engine/Entity.hpp"

#include "Player/Player.hpp"

using namespace Engine;
//
//
//
LocomotionManager::LocomotionManager(Player &in_player)
    : seek_locomotion(in_player.movable),
      head_locomotion(in_player.movable),
      pursue_locomotion(in_player.movable),
      pursue_til_caught_locomotion(in_player.movable) {}

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
void LocomotionManager::pursue(Movable &in_target){
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
void LocomotionManager::pursue_til_caught(Movable &in_target, float in_range){
  if (current_locomotion) {
    current_locomotion->stop();
  }
  pursue_til_caught_locomotion.init(in_target, in_range);
  current_locomotion = &pursue_til_caught_locomotion;
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
