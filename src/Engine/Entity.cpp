#include "Entity.hpp"
namespace Engine {
//
//
//
Entity::Entity() = default;
//
//
//
Engine::Direction Entity::directionTo(const Entity &in_entity) {
  Vector3 direction = in_entity.movable->position - movable->position;
  Compass c(direction.roundAngle(45).normalise());
  return c.direction;
}
}  // namespace Engine
