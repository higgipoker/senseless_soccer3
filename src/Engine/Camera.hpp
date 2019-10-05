#pragma once

#include "Entity.hpp"

#include <SFML/Graphics/View.hpp>

namespace Engine {
/**
 * @brief The Camera class
 */
class Camera : public Entity {
public:
  //
  //
  //
  Camera();
  //
  //
  //
  void update() override;
  //
  //
  //
  sf::View &getview();

private:
  sf::View view{sf::FloatRect{0, 0, 800, 600}};
};

} // namespace Engine
