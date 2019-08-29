#include "physics.hpp"


void integrate_euler(Entity &entity, const float dt){
 // drag
 entity.force =
     (entity.force - (entity.velocity.multiply2d(entity.co_friction * dt)));

 // acceleration = entity.force / mass
 Vector3 acceleration = entity.force / entity.mass;

 // difference in velocity = acceleration * difference time
 Vector3 dv = acceleration * dt;

 // velocity = velocity + difference in velocity
 entity.velocity += dv;

 // difference in position = velocity * difference time
 Vector3 dp = entity.velocity * dt;

 // update position
 entity.position += dp;
}

// -----------------------------------------------------------------------------
//  integrate
// -----------------------------------------------------------------------------
void integrate_improved_euler(Entity &entity, const float dt) {
 // step 1
 entity.force =
     (entity.force - (entity.velocity.multiply2d(entity.co_friction * dt)));
 Vector3 acceleration = entity.force / entity.mass;
 Vector3 k1 = acceleration * dt;

 // step 2
 entity.force =
     (entity.force - (entity.velocity + k1).multiply2d(entity.co_friction));
 acceleration = entity.force / entity.mass;
 Vector3 k2 = acceleration * dt;

 // update velocity
 entity.velocity = entity.velocity + (k1 + k2) / 2;

 // change in position (converted to pixels)
 Vector3 dp = (entity.velocity * dt);

 // apply new position
 entity.position = entity.position + dp;

 entity.force.reset();
}
