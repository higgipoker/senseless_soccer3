#include "entity.hpp"
// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void apply_force(Entity& entity, gamelib3::Vector3 force) {
  entity.force += force;
}
