#pragma once

#include "Entity.hpp"

#include <SFML/Graphics/CircleShape.hpp>
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
  Camera(float in_viewport_width, float in_viewport_height);
  //
  //
  //
  void follow(Entity &in_entity);
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
  //
  //
  //
  void setWorldRect(sf::FloatRect in_rect);

 private:
  sf::View view;
  sf::FloatRect world;
  Entity *following = nullptr;
};

}  // namespace Engine
