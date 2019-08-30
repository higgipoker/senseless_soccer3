#include "physics.hpp"

void integrate_euler(Entity &entity, const float dt) {
  // drag
  friction = entity.velocity.reverse();
  friction = friction * entity.co_friction * dt;
  entity.force = entity.force + friction;

  // acceleration = entity.force / mass
  acceleration = entity.force / entity.mass;

  // difference in velocity = acceleration * difference time
  dv = acceleration * dt;

  // velocity = velocity + difference in velocity
  entity.velocity += dv;

  if(entity.velocity.magnitude() > entity.terminal_velocity){
    entity.velocity = entity.velocity.setMagnitude(entity.terminal_velocity);
  }

  // difference in position = velocity * difference time
  dp = entity.velocity * dt;

  // update position
  entity.position += dp;

  // reset forces for next step
  entity.force.reset();
}

// -----------------------------------------------------------------------------
//  integrate
// -----------------------------------------------------------------------------
void integrate_improved_euler(Entity &entity, const float dt) {
  // step 1
  friction = entity.velocity.reverse();
  friction = friction * entity.co_friction * dt;
  entity.force = entity.force + friction;
  acceleration = entity.force / entity.mass;
  k1 = acceleration * dt;

  // step 2
  friction = entity.velocity.reverse();
  friction = friction * entity.co_friction * dt;
  entity.force = entity.force + friction;
  acceleration = entity.force / entity.mass;
  k2 = acceleration * dt;

  // update velocity
  entity.velocity = entity.velocity + (k1 + k2) / 2;

  // change in position (converted to pixels)
  dp = (entity.velocity * dt);

  // apply new position
  entity.position = entity.position + dp;

  // reset forces for next step
  entity.force.reset();
}
