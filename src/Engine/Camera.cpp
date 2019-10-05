#include "Camera.hpp"

#include <iostream>

namespace Engine {
//
//
//
Camera::Camera() {
  perspectivizable = false;
  movable.toggleGravity(false);
  movable.position.z = 50;
}
//
//
//
void Camera::update() {
  view.setCenter(movable.position.x, movable.position.y);
}
//
//
//
sf::View &Camera::getview() {
  return view;
}
} // namespace Engine
