#include "physics.hpp"
#include <gamelib2/math/vector.hpp>

static const float CLAMP_TO_GROUND = 0.000001f;
static const float GRAVITATIONAL_CONSTANT = -0.3f;

// -----------------------------------------------------------------------------
// bounce
// -----------------------------------------------------------------------------
inline void bounce(Entity &entity, const float dt) {
  // bounce
  entity.velocity.z = -entity.velocity.z;
  entity.velocity.z *= entity.co_bounciness;
  friction = entity.velocity.reverse();
  friction = friction * entity.co_friction * dt;
  entity.force = entity.force + friction;
}
// -----------------------------------------------------------------------------
// integrate
// -----------------------------------------------------------------------------
inline Vector3 integrate(Entity &entity, const float dt) {
  // step 1
  if (Floats::greater_than(entity.position.z, 0)) {
    // grabity
    Vector3 gravity;
    gravity.z = GRAVITATIONAL_CONSTANT * dt;
    entity.force += gravity * entity.mass * dt;
  } else {
    // drag
    friction = entity.velocity.reverse();
    friction = friction * entity.co_friction * dt;
    entity.force = entity.force + friction;
  }
  acceleration = entity.force / entity.mass;
  return acceleration * dt;
}
// -----------------------------------------------------------------------------
// damp_bounce
// -----------------------------------------------------------------------------
inline void damp_bounce(Entity &entity) {
  if (gamelib2::Floats::greater_than(fabsf(entity.velocity.z), 0)) {
    if (gamelib3::Floats::less_than(fabsf(entity.position.z),
                                    CLAMP_TO_GROUND)) {
      entity.position.z = 0;
      entity.velocity.z = 0;
    }
  }
}
// -----------------------------------------------------------------------------
// integrate_euler
// -----------------------------------------------------------------------------
void integrate_euler(Entity &entity, const float dt) {
  // moving down
  if (Floats::less_than(entity.velocity.z, 0) &&
      Floats::less_than(entity.position.z, 0)) {
    bounce(entity, dt);

  } else {
    if (Floats::greater_than(entity.position.z, 0)) {
      // grabity
      Vector3 gravity;
      gravity.z = GRAVITATIONAL_CONSTANT * dt;
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
  // dampens infinite bounce
  damp_bounce(entity);
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
    bounce(entity, dt);
  } else {
    // step 1
    auto k1 = integrate(entity, dt);

    // step 2
    auto k2 = integrate(entity, dt);

    // update velocity
    entity.velocity = entity.velocity + (k1 + k2) / 2;

    // change in position (converted to pixels)
    dp = (entity.velocity * dt);

    // apply new position
    entity.position = entity.position + dp;
  }
  // dampens infinite bounce
  damp_bounce(entity);
  // reset forces for next step
  entity.force.reset();
}

// -----------------------------------------------------------------------------
// circle with circle
// -----------------------------------------------------------------------------
bool collides(const sf::CircleShape &c1, const sf::CircleShape &c2) {
  if (Floats::equal(c1.getRadius(), 0) || Floats::equal(c2.getRadius(), 0)) {
    return false;
  }

  // compare the distance to combined radii
  float dx = c2.getPosition().x - c1.getPosition().x;
  float dy = c2.getPosition().y - c1.getPosition().y;
  float radii = c1.getRadius() + c2.getRadius();

  if ((dx * dx) + (dy * dy) < radii * radii) {
    return true;
  }

  return false;
}
