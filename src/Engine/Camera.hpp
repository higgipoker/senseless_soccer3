#pragma once

#include "Movable.hpp"

#include <SFML/Graphics/View.hpp>

namespace Engine {
/**
 * @brief The Camera class
 */
class Camera : public Movable {
 public:
  /**
   * @brief Camera
   */
  Camera();
  /**
   * @brief step
   * @param in_dt
   */
  void step(float in_dt);

  /// sf view
  sf::View view{sf::FloatRect{0, 0, 800, 600}};
};

}  // namespace Engine
