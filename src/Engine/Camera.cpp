#include "Camera.hpp"

#include <iostream>

namespace Engine {
//
//
//
Camera::Camera()
    : Entity(std::make_unique<Sprite>(), std::make_unique<Sprite>()) {
  movable.toggleGravity(false);
  movable.co_friction = 0.01F;
}
//
//
//
void Camera::handleInput() { Entity::handleInput(); }
//
//
//
void Camera::update() {
  {  // constrain in world
    const int bounce = 6;
    if ((movable.getX() - (view.getSize().x / 2)) < world.left) {
      movable.setX(world.left + view.getSize().x / 2);
      movable.applyForce({bounce, 0});
    }
    if ((movable.getX() + (view.getSize().x / 2)) > world.left + world.width) {
      movable.setX(world.left + world.width - view.getSize().x / 2);
      movable.applyForce({-bounce, 0});
    }
    if ((movable.getY() - (view.getSize().y / 2)) < world.top) {
      movable.setY(world.top + view.getSize().y / 2);
      movable.applyForce({0, bounce});
    }
    if ((movable.getY() + (view.getSize().y / 2)) > world.top + world.height) {
      movable.setY(world.top + world.height - view.getSize().y / 2);
      movable.applyForce({0, -bounce});
    }
  }
  view.setCenter(movable.getX(), movable.getY());
}
//
//
//
sf::View &Camera::getview() { return view; }
//
//
//
float Camera::getHeight() { return movable.getZ(); }
//
//
//
void Camera::setHeight(const float in_height) { movable.setZ(in_height); }
//
//
//
void Camera::setWorldRect(sf::IntRect in_rect) { world = in_rect; }
}  // namespace Engine
