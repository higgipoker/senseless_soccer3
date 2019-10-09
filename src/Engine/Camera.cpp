#include "Camera.hpp"

#include <iostream>

namespace Engine {
//
//
//
Camera::Camera() {
  perspectivizable = false;
  movable.toggleGravity(false);
  movable.co_friction = 0.01F;
}
//
//
//
void Camera::update() {
  view.setCenter(movable.getX(), movable.getY());
}
//
//
//
sf::View &Camera::getview() {
  return view;
}
//
//
//
float Camera::getHeight(){
  return movable.getZ();
}
//
//
//
void Camera::setHeight(const float in_height){
  movable.setZ(in_height);
}
} // namespace Engine
