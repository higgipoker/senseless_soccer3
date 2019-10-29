#include "Entity.hpp"

#include "Metrics.hpp"

#include <cassert>
#include <iostream>
namespace Engine {
//
//
//
Entity::Entity(UniquePtr<Sprite> in_sprite, UniquePtr<Sprite> in_shadow)
    : sprite(std::move(in_sprite)), shadow(std::move(in_shadow)) {
  sprite->shadow = shadow.get();
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
  if (input->fireDown()) {
    movable.applyForce({0.F, 0.F, speed * 1.F});
  }
}
//
//
//
void Entity::update(const float in_dt) {
  movable.step(in_dt);
  sprite->setPosition(movable.position.x, movable.position.y);
  shadow->setPosition({sprite->getPosition().x + shadow_offset,
                       sprite->getPosition().y + shadow_offset});
  sprite->animate();
  sprite->entity_height = movable.position.z;
  sprite->z = movable.position.y;
}
//
//
//
Vector3 Entity::directionTo(const Entity &in_entity, bool in_2d) const {
  auto ret = in_entity.movable.position - movable.position;
  if (in_2d) {
    ret.z = 0;
  }
  return ret;
}
//
//
//
void Entity::attachInput(InputDevice &in_device) {
  input = &in_device;
  in_device.attachListener(*this);
}
//
//
//
void Entity::detachInput() {
  assert("input is null" && input);
  input = nullptr;
}
//
//
//
InputDevice &Entity::getInputDevice() const {
  assert(
      "No input device is attached to this entity, call isInputAttached "
      "first." &&
      input);
  return *input;
}
//
//
//
bool Entity::isInputAttached() { return input != nullptr; }
//
//
//
Sprite &Entity::getSprite() { return *sprite.get(); }
//
//
//
Sprite &Entity::getShadow() { return *shadow.get(); }
}  // namespace Engine
