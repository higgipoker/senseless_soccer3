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
  Ball(Engine::Sprite& in_sprite, Engine::Sprite& in_shadow);
  //
  //
  //
  void update() override;
  //
  //
  //
  sf::CircleShape collidable;

 protected:
  float radius = 3;
};
