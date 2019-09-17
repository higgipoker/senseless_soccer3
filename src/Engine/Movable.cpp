#include "Movable.hpp"
namespace Engine {
static const float CLAMP_TO_GROUND = 0.0000001F;
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
  velocity.z = -velocity.z;
  velocity.z *= co_bounciness;
  friction = velocity.reverse();
  friction = friction * co_friction;
  force = force + friction;
}
//
//
//
void Movable::damp_bounce() {
  if (Floats::greater_than(fabsf(velocity.z), 0)) {
    if (Floats::less_than(fabsf(position.z), CLAMP_TO_GROUND)) {
      position.z = 0;
      velocity.z = 0;
    }
  }
}
//
//
//
void Movable::damp_velocity() {
  if (Floats::less_than(velocity.magnitude2d(), 0)) {
    velocity.reset();
  }
}
//
//
//
void Movable::integrate_improved_euler(const float in_dt) {
  // moving down
  if (Floats::less_than(velocity.z, 0) && Floats::less_than(position.z, 0)) {
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
    if (Floats::greater_than(dp.magnitude(), 0)) {
      auto mag = dp.magnitude2d();
      dp = dp.normalise2d();
      dp.x *= mag * speed;
      dp.y *= mag * speed;
    }
    // apply new position
    position = position + dp;
  }
  // dampens infinite bounce
  damp_bounce();
  // for very small velocities
  damp_velocity();
  // reset forces for next step
  force.reset();
}
//
//
//
Vector3 Movable::integrate(const float in_dt) {
  if (Floats::greater_than(position.z, 0)) {
    // gravity
    Vector3 gravity;
    gravity.z = GRAVITATIONAL_CONSTANT;
    force += gravity * mass * in_dt;
    // air resistance
    Vector3 air_resistance = velocity.reverse().normalise();
    air_resistance *= co_air_resistance;
    force += air_resistance * in_dt;

  } else {
    // drag
    if (Floats::greater_than(velocity.magnitude2d(), 0)) {
      friction = velocity.reverse();
      friction = friction * co_friction;
      velocity = velocity + friction;
    }
  }
  acceleration = force / mass * speed;
  return acceleration;
}
}  // namespace Engine
