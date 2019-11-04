#pragma once

#include "Engine/Entity.hpp"

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

/**
 * @brief The Ball class
 */
class Ball : public Engine::Entity {
 public:
  //
  //
  //
  Ball(UniquePtr<Engine::Sprite> in_sprite,
       UniquePtr<Engine::Sprite> in_shadow);
  //
  //
  //
  void update() override;
  //
  //
  //
  void kick(Engine::Vector3 in_force);
  //
  //
  //
  void applyTopSpin(float in_factor);
  //
  //
  //
  void applyBackSpin(float in_factor);
  //
  //
  //
  void applySideSpin(Engine::Vector3 in_spin);
  //
  //
  //
  sf::CircleShape collidable;

  // tmp diagnostics
  void start_recording_distance() {
    distance = 0;
    recording_distance = true;
    initial_position = movable.position;
  }
  void stop_recording_distance() { recording_distance = false; }
  bool recording_distance = false;
  float distance;
  Engine::Vector3 initial_position;
  Engine::Vector3 last_position;
  float last_force=0;

 protected:
  float radius = 3;
  //
  //
  //
  void debug();
};
