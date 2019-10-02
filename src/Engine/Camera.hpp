#pragma once

#include "Entity.hpp"

#include <SFML/Graphics/View.hpp>

namespace Engine {
/**
 * @brief The Camera class
 */
class Camera : public Entity {
 public:
  /**
   * @brief step
   * @param in_dt
   */
  void step(float in_dt);
  /// sf view
  sf::View view{sf::FloatRect{0, 0, 800, 600}};
  /// camera height off the ground
  const float height = 50;
};

}  // namespace Engine
