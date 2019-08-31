#include "physics.hpp"

void integrate_euler(Entity &entity, const float dt) {
  // moving down
  if (Floats::less_than(entity.velocity.z, 0) &&
      Floats::less_than(entity.position.z, 0)) {
    // bounce
    entity.position.z = 0;
    entity.velocity.z = -entity.velocity.z;
    entity.velocity.z *= 0.9f;
    friction = entity.velocity.reverse();
    friction = friction * entity.co_friction * dt;
    entity.force = entity.force + friction;

  } else {
    if (Floats::greater_than(entity.position.z, 0)) {
      // grabity
      Vector3 gravity;
      gravity.z = -0.05f * dt;
      entity.force += gravity * entity.mass * dt;
    } else {
      // drag
      friction = entity.velocity.reverse();
      friction = friction * entity.co_friction * dt;
      entity.force = entity.force + friction;
    }

    // acceleration = entity.force / mass
    acceleration = entity.force / entity.mass;

    // difference in velocity = acceleration * difference time
    dv = acceleration * dt;

    // velocity = velocity + difference in velocity
    entity.velocity += dv;

    // difference in position = velocity * difference time
    dp = entity.velocity * dt;

    // update position
    entity.position += dp;
  }
  // reset forces for next step
  entity.force.reset();
}

// -----------------------------------------------------------------------------
//  integrate
// -----------------------------------------------------------------------------
void integrate_improved_euler(Entity &entity, const float dt) {
  // moving down
  if (Floats::less_than(entity.velocity.z, 0) &&
      Floats::less_than(entity.position.z, 0)) {
    // bounce
    entity.position.z = 0;
    entity.velocity.z = -entity.velocity.z;
    entity.velocity.z *= 0.9f;
    friction = entity.velocity.reverse();
    friction = friction * entity.co_friction * dt;
    entity.force = entity.force + friction;

  } else {
    // step 1
    if (Floats::greater_than(entity.position.z, 0)) {
      // grabity
      Vector3 gravity;
      gravity.z = -0.1f * dt;
      entity.force += gravity * entity.mass * dt;
    } else {
      // drag
      friction = entity.velocity.reverse();
      friction = friction * entity.co_friction * dt;
      entity.force = entity.force + friction;
    }
    acceleration = entity.force / entity.mass;
    k1 = acceleration * dt;

    // step 2
    if (Floats::greater_than(entity.position.z, 0)) {
      // grabity
      Vector3 gravity;
      gravity.z = -0.1f * dt;
      entity.force += gravity * entity.mass * dt;
    } else {
      // drag
      friction = entity.velocity.reverse();
      friction = friction * entity.co_friction * dt;
      entity.force = entity.force + friction;
    }
    acceleration = entity.force / entity.mass;
    k2 = acceleration * dt;

    // update velocity
    entity.velocity = entity.velocity + (k1 + k2) / 2;

    // change in position (converted to pixels)
    dp = (entity.velocity * dt);

    // apply new position
    entity.position = entity.position + dp;
  }

  // reset forces for next step
  entity.force.reset();
}
