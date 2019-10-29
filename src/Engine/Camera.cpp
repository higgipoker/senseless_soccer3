#include "Camera.hpp"

#include "Engine/Collider.hpp"

#include <iostream>

namespace Engine {
//
//
//
Camera::Camera(float in_viewport_width, float in_viewport_height)
    : Entity(std::make_unique<Sprite>(), std::make_unique<Sprite>()),
      view{{0, 0, in_viewport_width, in_viewport_height}},
      collider(in_viewport_width / 6) {
  movable.toggleGravity(false);
  movable.properties.co_friction = 0.01F;
  speed = 1;
  collider.setOutlineColor(sf::Color::Blue);
  collider.setOutlineThickness(3);
  collider.setFillColor(sf::Color(0, 0, 0, 0));
}
//
//
//
void Camera::follow(Entity &in_entity) {
  movable.position.x = in_entity.movable.position.x;
  movable.position.y = in_entity.movable.position.y;
  view.setCenter(movable.position.x, movable.position.y);
  following = &in_entity;
}
//
//
//
void Camera::handleInput() { Entity::handleInput(); }
//
//
//
void Camera::update(const float in_dt) {
  movable.step(in_dt);
  view.setCenter(movable.position.x, movable.position.y);
  collider.setCenter(movable.position.x, movable.position.y);

  if (following) {
    if (!Collider::contains(collider, following->movable.position)) {
      Vector3 force = directionTo(*following);
      force.normalise2d();
      force *= speed * following->movable.velocity.magnitude2d();
      movable.applyForce(force);
    }
  }

  //  {  // constrain in world
  //    if ((movable.position.x - (view.getSize().x / 2)) < world.left) {
  //      movable.velocity.x = 0;
  //      movable.force.x = 0;
  //    }
  //    if ((movable.position.x + (view.getSize().x / 2)) > world.left +
  //    world.width) {
  //      movable.velocity.x = 0;
  //      movable.force.x = 0;
  //    }
  //    if ((movable.position.y - (view.getSize().y / 2)) < world.top) {
  //      movable.velocity.y = 0;
  //      movable.force.y = 0;
  //    }
  //    if ((movable.position.y + (view.getSize().y / 2)) > world.top +
  //    world.height) {
  //      movable.velocity.y = 0;
  //      movable.force.y = 0;
  //    }
  //  }

  sprite->debug_shapes.clear();
  sprite->debug_shapes.push_back(&collider);
}
//
//
//
sf::View &Camera::getview() { return view; }
//
//
//
float Camera::getHeight() { return movable.position.z; }
//
//
//
void Camera::setHeight(const float in_height) {
  movable.position.z = in_height;
}
//
//
//
void Camera::setWorldRect(sf::IntRect in_rect) { world = in_rect; }
}  // namespace Engine
