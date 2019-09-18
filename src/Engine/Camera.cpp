#include "Camera.hpp"
namespace Engine {
//
//
//
Camera::Camera() {}
//
//
//
void Camera::step(float in_dt) {
  //test
  position.x++;
  view.setCenter(position.x, position.y); }
}  // namespace Engine
