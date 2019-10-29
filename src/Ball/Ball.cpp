#include "Ball.hpp"

#include "Engine/Debug.hpp"
#include "Engine/Types.hpp"

#include <iostream>
using namespace Engine;
//
//
//
Ball::Ball(UniquePtr<Sprite> in_sprite, UniquePtr<Sprite> in_shadow)
    : Entity(std::move(in_sprite), std::move(in_shadow)) {
  collidable.setRadius(radius);
  movable.properties.co_friction = 0.01F;
  movable.properties.co_bounciness = 0.85f;
  movable.properties.cross_section = radius * 2;
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
void Ball::update(const float in_dt) {
  Entity::update(in_dt);

  // update collidable object
  collidable.setCenter(movable.position.x, movable.position.y);

  // sprite only animates if moving
  if (Math::greater_than(movable.velocity.magnitude(), 0)) {
    // sprite rotates in direction of movement (unless spin...later!!)
    const float offset = 180;  // according to the spritesheet image
    sprite->setRotation(movable.velocity.angle() + offset);
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

  if (DRAW_RAYS) {
    xray.setSize({10000, 1});
    xray.setPosition(0, collidable.getCenter().y);
    xray.setFillColor(sf::Color::Magenta);
    sprite->debug_shapes.push_back(&xray);

    yray.setSize({1, 10000});
    yray.setPosition(collidable.getCenter().x, 0);
    yray.setFillColor(sf::Color::Magenta);
    sprite->debug_shapes.push_back(&yray);
  }
}
//
//
//
void Ball::kick(Vector3 in_force) {
  movable.resetForces();
  movable.resetVelocity();
  movable.applyForce(in_force);
}
//
//
//
void Ball::applyTopSpin(float in_factor) {
  Vector3 spin{0.F, 0.F, -in_factor};
  movable.forces.topspin += spin;
}
//
//
//
void Ball::applyBackSpin(float in_factor) {}
//
//
//
void Ball::applySideSpin(Engine::Vector3 in_spin) {
  // todo can't be spinning in opposite dirs at once
  movable.forces.sidespin+=in_spin;
}
