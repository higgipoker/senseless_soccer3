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
  movable.co_bounciness = 0.8f;
}
//
//
//
void Ball::handleInput() { Entity::handleInput(); }
//
//
//
void Ball::update() {
  Entity::update();

  // update collidable object
  collidable.setCenter(movable.getX(), movable.getY());

  // spriteonly animates if moving
  if (Math::greater_than(movable.getVelocityMag(), 0)) {
    // sprite rotates in direction of movement (unless spin...later!!)
    constexpr float offset = 180;  // according to the spritesheet image
    sprite.setRotation(movable.getVelocity().angle() + offset);
    sprite.startAnimating();
  } else {
    sprite.stopAnimating();    
  }
}
