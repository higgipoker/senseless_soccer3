#pragma once

#include "Engine/Entity.hpp"

#include <SFML/Graphics/CircleShape.hpp>

/**
 * @brief The Ball class
 */
class Ball : public Engine::Entity {
 public:
  //
  //
  //
  Ball(UniquePtr<Engine::Sprite> in_sprite, UniquePtr<Engine::Sprite> in_shadow);
  //
  //
  //
  void handleInput() override;
  //
  //
  //
  void update(const float in_dt) override;
  //
  //
  //
  void kick(Engine::Vector3 in_force);
  //
  //
  //
  sf::CircleShape collidable;

 protected:
  float radius = 3;
  //
  //
  //
  void debug();
};
