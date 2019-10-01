#include "Movable.hpp"
//
//
//
namespace Engine {
//
//
//
static const float CLAMP_TO_GROUND = 0.458F;
static const float GRAVITATIONAL_CONSTANT = 9.8F;
//
//
//
Movable::Movable() {}
//
//
//
void Movable::step(float in_dt) { integrate_improved_euler(in_dt); }
//
//
//
void Movable::bounce() {
  position.z = 0;
  velocity.z = -velocity.z;
  velocity.z *= co_bounciness;
  friction = velocity;
  friction.reverse();
  friction = friction * co_friction;
  force = force + friction;
  // dampens infinite bounce
  damp_bounce();
}
//
//
//
void Movable::damp_bounce() {
  if (Math::less_than(fabsf(velocity.z), CLAMP_TO_GROUND)) {
    position.z = 0;
    velocity.z = 0;
  }
}
//
//
//
void Movable::damp_velocity() {
  if (Math::less_than(velocity.magnitude2d(), 0)) {
    velocity.reset();
  }
}
//
//
//
void Movable::integrate_improved_euler(const float in_dt) {
  // moving down
  if (Math::less_than(velocity.z, 0) && Math::less_than(position.z, 0)) {
    bounce();
  } else {
    // step 1
    k1 = integrate(in_dt);
    // step 2
    k2 = integrate(in_dt);
    // update velocity
    velocity = velocity + (k1 + k2) / 2;
    // change in position (converted to pixels)
    dp = (velocity);
    // normalizes for diagonals
    if (Math::greater_than(dp.magnitude(), 0)) {
      auto mag = dp.magnitude2d();
      dp.normalise2d();
      dp.x *= mag * speed;
      dp.y *= mag * speed;
    }
    // apply new position
    position = position + dp;
  }
  // for very small velocities
  damp_velocity();
  // reset forces for next step
  force.reset();
}
//
//
//
Vector3 Movable::integrate(const float in_dt) {
  if (Math::greater_than(position.z, 0)) {
    // gravity
    Vector3 gravity;
    gravity.z = -GRAVITATIONAL_CONSTANT;
    force += gravity * mass * in_dt;
    // air resistance
    Vector3 air_resistance = velocity;
    air_resistance.reverse();
    air_resistance.normalise();
    air_resistance *= co_air_resistance;
    force += air_resistance * in_dt;

  } else {
    // drag
    if (Math::greater_than(velocity.magnitude2d(), 0)) {
      friction = velocity;
      friction.reverse();
      friction = friction * co_friction;
      velocity = velocity + friction;
    }
  }
  acceleration = force / mass * speed;
  return acceleration;
}
}  // namespace Engine
