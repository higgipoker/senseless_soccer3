#include "Entity.hpp"

#include "Metrics.hpp"

#include <iostream>
namespace Engine {
Sprite Entity::dummy_sprite;
Sprite Entity::dummy_shadow;
//
//
//
Entity::Entity() : sprite(dummy_sprite), shadow(dummy_shadow) {}
//
//
//
Entity::Entity(Sprite &in_sprite, Sprite &in_shadow)
    : sprite(in_sprite), shadow(in_shadow) {
  sprite.shadow = &shadow;
}
//
//
//
void Entity::handleInput() {
  if (!input) return;

  if (input->up()) {
    movable.applyForce({0, -speed});
  }
  if (input->down()) {
    movable.applyForce({0, speed});
  }
  if (input->left()) {
    movable.applyForce({-speed, 0});
  }
  if (input->right()) {
    movable.applyForce({speed, 0});
  }
  if (input->fire_down()) {
    movable.applyForce({0.F, 0.F, speed*1.F});
  }
}
//
//
//
void Entity::update() {
  sprite.setPosition(movable.getX(), movable.getY());
  shadow.setPosition(sprite.getPosition());
  shadow.move(shadow_offset, shadow_offset);
  sprite.animate();
  sprite.entity_height = movable.getZ();
}
//
//
//
Direction Entity::directionTo(const Entity &in_entity) const {
  Vector3 direction = in_entity.movable.getPosition() - movable.getPosition();
  direction.roundAngle(45);
  direction.normalise();
  Compass c(direction);
  return c.direction;
}
//
//
//
void Entity::attachInput(InputDevice &in_device) { input = &in_device; }
//
//
//
void Entity::detachInput() { input = nullptr; }
//
//
//
InputDevice *Entity::getInput() const { return input; }
}  // namespace Engine
