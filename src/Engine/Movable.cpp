#include "Movable.hpp"
//
namespace Senseless {
//
static const float CLAMP_TO_GROUND = 0.01F;
static const float GRAVITATIONAL_CONSTANT = 9.8F;
//
//
//
void Movable::setPosition(const float in_x, const float in_y, const float in_z) {
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
void Movable::setPosition(const sf::Vector2f in_point) {
  position = {in_point.x, in_point.y, 0.0F};
}
//
//
//
void Movable::move(const float in_dx, const float in_dy) {
  position.x += in_dx;
  position.y += in_dy;
}
//
//
//
void Movable::resetVelocity() { Vector::reset(velocity); }
//
//
//
void Senseless::Movable::applyForce (const sf::Vector3f &in_force) { forces.force += in_force; }
//
//
//
void Movable::resetForces() { forces.reset(); }
//
//
//
void Movable::step(const float in_dt) {
  // bounce
  if (Math::less_than(velocity.z, 0) && Math::less_than(position.z, 0)) {
    velocity.z = -velocity.z;
    velocity.z *= properties.co_bounciness;
    // damp bounce
    if (Math::less_than(fabsf(position.z), CLAMP_TO_GROUND)) {
      position.z = 0;
      velocity.z = 0;
    }
  }

  integrate_improved_euler(in_dt);

  // damp velocity
  if (Math::equal(Vector::magnitude(velocity), 0)) {
    Vector::reset(velocity);
  }

  // decay spin
  forces.topspin *= properties.co_spin_decay;
  forces.sidespin *= properties.co_spin_decay;

  forces.reset();
}
//
//
//
void Movable::integrate_improved_euler(const float in_dt) {
  sf::Vector3f acceleration1 = integrate(in_dt);
  sf::Vector3f acceleration2 = integrate(in_dt);
  velocity = velocity + (acceleration1 + acceleration2) / 2.F;
  position = position + velocity;
}
//
//
//
sf::Vector3f Movable::integrate(const float in_dt) {
  if (Math::greater_than(position.z, 0) && affected_by_gravity) {
    // gravity
    sf::Vector3f gravity;
    gravity.z = -GRAVITATIONAL_CONSTANT;
    forces.force += gravity * properties.mass * in_dt;

    // air drag = (air density * co_drag * cross section area) / 2
    // in the opposite direction to velocity
    sf::Vector3f drag = velocity;
    Vector::reverse(drag);
    Vector::normalise(drag);
    drag = drag * (environment.air_density * properties.co_air_resistance *
                   (Math::PI * properties.cross_section * properties.cross_section) / 2);
    forces.force += drag * in_dt;

    // spin in the air (magnus)
    forces.force += forces.topspin;
    forces.force += forces.sidespin;

  } else {
    // firction
    if (Math::greater_than(Vector::magnitude2d(velocity), 0)) {
      sf::Vector3f friction = velocity;
      Vector::reverse(friction);
      friction = friction * properties.co_friction;
      velocity = velocity + friction;
    }

    // spin on the ground
  }

  // return acceleration (f=ma)
  return forces.force / properties.mass;
}
//
//
//
void Movable::toggleGravity(const bool in_status) { affected_by_gravity = in_status; }
//
//
//
void Movable::place(const sf::Vector3f &in_position) {
  resetVelocity();
  resetForces();
  position = in_position;
}
//
//
//
void Movable::setBounds(sf::FloatRect in_bounds) { bounds = in_bounds; }
//
//
//
sf::FloatRect Movable::getBounds() { return bounds; }
}  // namespace Senseless
