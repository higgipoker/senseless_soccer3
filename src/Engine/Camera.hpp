#pragma once

#include "Entity.hpp"

#include <SFML/Graphics/View.hpp>

namespace Engine {
//
//
//
class Camera : public Entity {
 public:
  //
  //
  //
  Camera();
  //
  //
  //
  void handleInput() override;
  //
  //
  //
  void update() override;
  //
  //
  //
  sf::View &getview();
  //
  //
  //
  float getHeight();
  //
  //
  //
  void setHeight(const float in_height);

 private:
  sf::View view{sf::FloatRect{0, 0, 800, 600}};
};

}  // namespace Engine
