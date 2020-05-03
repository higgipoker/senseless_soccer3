#pragma once

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

#include "Engine/Entity.hpp"
namespace Senseless {
/**
 * @brief The Ball class
 */
class Ball : public Entity {
 public:
  //
  //
  //
  Ball(UniquePtr<Sprite> in_sprite, UniquePtr<Sprite> in_shadow);
  //
  //
  //
  void update() override;
  //
  //
  //
  void kick(Vector3 in_force);
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
  void applySideSpin(Vector3 in_spin);
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
  Vector3 initial_position;
  Vector3 last_position;
  float last_force = 0;

 protected:
  float radius = 3;
  //
  //
  //
  void debug();
};
}  // namespace Senseless
