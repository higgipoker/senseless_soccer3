#include "Camera.hpp"

#include <iostream>

namespace Engine {
//
//
//
Camera::Camera() {
  movable.toggleGravity(false);
  movable.co_friction = 0.01F;
}
//
//
//
void Camera::handleInput() {
  Entity::handleInput();
}
//
//
//
void Camera::update() { view.setCenter(movable.getX(), movable.getY());
                      std::cout << movable.getZ() << std::endl;}
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

}  // namespace Engine
