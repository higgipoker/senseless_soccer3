#include "entity.hpp"
#include "data.hpp"
//
//
//
Entity &get_entity(int id) { return entity_pool[id]; }
//
//
//
void apply_force(Entity &entity, Vector3 force) { entity.force += force; }
//
//
//
Direction direction_to(const Entity &from, const Entity &to) {
  Vector3 direction = to.position - from.position;
  Compass c(direction.roundAngle(45).normalise());
  return c.direction;
}
//
//
//
Direction direction_to(const Vector3 &from, const Vector3 &to) {
  Vector3 direction = to - from;
  Compass c(direction.roundAngle(45).normalise());
  return c.direction;
}
