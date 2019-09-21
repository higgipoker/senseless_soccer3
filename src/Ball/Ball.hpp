#pragma once

#include "Engine/Entity.hpp"

#include <SFML/Graphics/CircleShape.hpp>

/**
 * @brief The Ball class
 */
class Ball : public Engine::Entity {
 public:
  /**
   * @brief Ball
   */
  Ball(Engine::Sprite & in_sprite, Engine::Sprite & in_shadow);

  /**
   * @brief Update
   */
  void update();

  sf::CircleShape collidable;

  Engine::Movable movable;

 protected:
  float radius = 3;

};
