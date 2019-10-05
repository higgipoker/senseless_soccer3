#include "Movable.hpp"
//
namespace Engine {
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
const Vector3 Movable::getPosition() const { return position; }
//
//
//
void Movable::setPosition(const Vector3 &in_position) {
  position = in_position;
}
//
//
//
void Movable::setPosition(const float in_x, const float in_y,
                          const float in_z) {
  position = {in_x, in_y, in_z};
}
//
//
//
void Movable::setPosition(const float in_x, const float in_y) {
  position = {in_x, in_y, position.z};
}
//
//
//
void Movable::move(float in_dx, float in_dy){
  position.x += in_dx;
  position.y += in_dy;
}
//
//
//
float Movable::getX() const { return position.x; }
//
//
//
float Movable::getY() const { return position.y; }
//
//
//
float Movable::getZ() const { return position.z; }
//
//
//
void Movable::setX(float in_x){
  position.x = in_x;
}
//
//
//
void Movable::setY(float in_y){
  position.y = in_y;
}
//
//
//
void Movable::setZ(float in_z){
  position.z = in_z;
}
//
//
//
const Vector3 Movable::getVelocity() const { return velocity; }
//
//
//
float Movable::getVelocityMag(bool in_2d){
  return in_2d ? velocity.magnitude2d() : velocity.magnitude();
}
//
//
//
void Movable::setVelocity(const Vector3 &in_velocity){
  velocity = in_velocity;
}
//
//
//
void Movable::resetVelocity(){
  velocity.reset();
}
//
//
//
void Movable::normalizeVelocity(bool in_2d){
  in_2d ? velocity.normalise2d() :  velocity.normalise();
}
//
//
//
void Movable::applyForce(Vector3 in_force){
  force += in_force;
}
//
//
//
void Movable::resetForces(){
  force.reset();
}
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
  Vector3 friction = velocity;
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
    Vector3 k1 = integrate(in_dt);
    // step 2
    Vector3 k2 = integrate(in_dt);
    // update velocity
    velocity = velocity + (k1 + k2) / 2;
    // change in position (converted to pixels)
    Vector3 dp = (velocity);
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
  if (Math::greater_than(position.z, 0) && affected_by_gravity) {
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
      Vector3 friction = velocity;
      friction.reverse();
      friction = friction * co_friction;
      velocity = velocity + friction;
    }
  }
  Vector3 acceleration = force / mass * speed;
  return acceleration;
}
//
//
//
void Movable::toggleGravity(bool in_status) { affected_by_gravity = in_status; }
}  // namespace Engine
