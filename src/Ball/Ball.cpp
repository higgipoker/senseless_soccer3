#include "Ball.hpp"

#include <iostream>
using namespace Engine;
//
//
//
Ball::Ball(Sprite &in_sprite, Sprite &in_shadow)
    : Entity(in_sprite, in_shadow) {
  // todo ball radius
  perspective_width = radius * 2;
  collidable.setRadius(radius);
  movable.co_friction = 0.01F;
  movable.co_bounciness=0.8f;
}
//
//
//
void Ball::update() {
  Entity::update();
  sprite.setRotation(movable.getVelocity().angle());
  std::cout << movable.getVelocity().angle() << std::endl;
  sprite.animate();
  collidable.setPosition(movable.getX() - collidable.getRadius(),
                         movable.getY() - collidable.getRadius());
}
