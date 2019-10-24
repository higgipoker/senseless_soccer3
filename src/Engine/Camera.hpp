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
  void update(const float in_dt) override;
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
  //
  //
  //
  void setWorldRect(sf::IntRect in_rect);

 private:
  sf::View view{sf::FloatRect{0, 0, 800, 600}};
  sf::IntRect world;
};

}  // namespace Engine
