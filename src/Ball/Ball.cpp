#include "Ball.hpp"

#include "Engine/Debug.hpp"
#include "Engine/Types.hpp"

#include <iostream>
using namespace Engine;
//
//
//
Ball::Ball(UnqPtr<Sprite> in_sprite, UnqPtr<Sprite> in_shadow)
    : Entity(std::move(in_sprite), std::move(in_shadow)) {
  // todo ball radius
  collidable.setRadius(radius);
  movable.co_friction = 0.01F;
  movable.co_bounciness = 0.8f;
  sprite->setBasePerspectiveWidth(radius * 2);
  shadow->setBasePerspectiveWidth(radius * 2);
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

  // sprite only animates if moving
  if (Math::greater_than(movable.getVelocityMag(), 0)) {
    // sprite rotates in direction of movement (unless spin...later!!)
    constexpr float offset = 180;  // according to the spritesheet image
    sprite->setRotation(movable.getVelocity().angle() + offset);
    sprite->startAnimating();
  } else {
    sprite->stopAnimating();
  }
#ifndef NDEBUG
  debug();
#endif
}
//
//
//
void Ball::debug() {
  collidable.setFillColor(sf::Color::Transparent);
  collidable.setOutlineThickness(1);
  collidable.setOutlineColor(Debug::defaultDiagnosticsColor());

  sprite->debug_shapes.clear();
  sprite->debug_shapes.push_back(&collidable);
}
//
//
//
void Ball::kick(Vector3 in_force) {
  movable.resetForces();
  movable.resetVelocity();
  movable.applyForce(in_force);
}
