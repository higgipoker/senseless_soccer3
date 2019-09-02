#include "entity.hpp"
#include "data.hpp"
//
//
//
Entity& get_entity(int id) { return entity_pool[id]; }
//
//
//
void apply_force(Entity& entity, Vector3 force) { entity.force += force; }
//
//
//
Direction direction_to(Entity& from, Entity& to) {
  Vector3 direction = to.position - from.position;
  Compass c(direction.normalise());
  return c.direction;
}
