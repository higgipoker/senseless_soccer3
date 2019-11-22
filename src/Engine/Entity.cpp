#include "Entity.hpp"

#include <cassert>
#include <iostream>

#include "Metrics.hpp"
namespace Engine {
//
//
//
Entity::Entity() {}
//
//
//
Entity::Entity(UniquePtr<Sprite> in_sprite) : sprite(std::move(in_sprite)) {}
//
//
//
Entity::Entity(UniquePtr<Sprite> in_sprite, UniquePtr<Sprite> in_shadow)
    : sprite(std::move(in_sprite)), shadow(std::move(in_shadow)) {
  sprite->shadow = shadow.get();
  has_shadow = true;
}
//
//
//
void Entity::update() {
  sprite->setPosition(movable.position.x, movable.position.y);
  if (hasShadow()) {
    shadow->setPosition({sprite->getPosition().x + shadow_offset,
                         sprite->getPosition().y + shadow_offset});
  }
  sprite->animate();
  sprite->entity_height = movable.position.z;
  sprite->z = static_cast<int>(movable.position.y);

  movable.setBounds(sprite->getGlobalBounds());
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
float Entity::distanceTo(const Entity &in_entity) const {
  auto ret = (in_entity.movable.position - movable.position).magnitude();
  return ret;
}
//
//
//
Sprite &Entity::getSprite() { return *sprite.get(); }
//
//
//
Sprite &Entity::getShadow() { return *shadow.get(); }
}  // namespace Engine
