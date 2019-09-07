#include "physics.hpp"

#include "vector.hpp"

static const float CLAMP_TO_GROUND = 0.0000001f;
static const float GRAVITATIONAL_CONSTANT = -9.8f;
//
//
//
inline void damp_velocity(Entity &entity) {
  if (entity.velocity.magnitude2d() < TOL) {
    entity.velocity.reset();
  }
}
//
//
//
inline void bounce(Entity &entity) {
  // bounce
  entity.velocity.z = -entity.velocity.z;
  entity.velocity.z *= entity.co_bounciness;
  friction = entity.velocity.reverse();
  friction = friction * entity.co_friction;
  entity.force = entity.force + friction;
}
//
//
//
inline void damp_bounce(Entity &entity) {
  if (Floats::greater_than(fabsf(entity.velocity.z), 0)) {
    if (Floats::less_than(fabsf(entity.position.z), CLAMP_TO_GROUND)) {
      entity.position.z = 0;
      entity.velocity.z = 0;
    }
  }
}
//
//
//
inline Vector3 integrate(Entity &entity, const float dt) {
  if (Floats::greater_than(entity.force.z, 0)) {
    int a = 0;
  }

  if (Floats::greater_than(entity.position.z, 0)) {
    // gravity
    Vector3 gravity;
    gravity.z = GRAVITATIONAL_CONSTANT;
    entity.force += gravity * entity.mass * dt;
    // air resistance
    Vector3 air_resistance = entity.velocity.reverse().normalise();
    air_resistance *= entity.co_air_resistance;
    entity.force += air_resistance * dt;

  } else {
    // drag
    if (Floats::greater_than(entity.velocity.magnitude2d(), 0)) {
      friction = entity.velocity.reverse();
      friction = friction * entity.co_friction;
      entity.velocity = entity.velocity + friction;
    }
  }
  acceleration = entity.force / entity.mass * entity.speed;
  return acceleration;
}
//
//
//
void integrate_euler(Entity &entity, const float dt) {
  // moving down
  bool bounced = false;
  if (Floats::less_than(entity.velocity.z, 0) &&
      Floats::less_than(entity.position.z, 0)) {
    bounce(entity);
    bounced = true;

  } else {
    if (Floats::greater_than(entity.position.z, 0)) {
      // gravity
      Vector3 gravity;
      gravity.z = GRAVITATIONAL_CONSTANT;
      entity.force += gravity * entity.mass * dt;
    } else {
      // friction
      friction = entity.velocity.reverse();
      friction = friction * entity.co_friction;
      entity.velocity = entity.velocity + friction;
    }

    // acceleration = entity.force / mass
    acceleration = entity.force / entity.mass;

    // difference in velocity = acceleration * difference time
    dv = acceleration;

    // velocity = velocity + difference in velocity
    entity.velocity += dv;

    // difference in position = velocity * difference time
    dp = entity.velocity;

    // update position
    entity.position += dp;
  }
  // dampens infinite bounce
  if (bounced) {
    damp_bounce(entity);
  }
  // reset forces for next step
  entity.force.reset();
}
//
//
//
void integrate_improved_euler(Entity &entity, const float dt) {
  // moving down
  if (Floats::less_than(entity.velocity.z, 0) &&
      Floats::less_than(entity.position.z, 0)) {
    bounce(entity);
  } else {
    // step 1
    k1 = integrate(entity, dt);
    // step 2
    k2 = integrate(entity, dt);
    // update velocity
    entity.velocity = entity.velocity + (k1 + k2) / 2;
    // change in position (converted to pixels)
    dp = (entity.velocity);
    // normalizes for diagonals
    if (Floats::greater_than(dp.magnitude(), 0)) {
      auto mag = dp.magnitude2d();
      dp = dp.normalise2d();
      dp.x *= mag * entity.speed;
      dp.y *= mag * entity.speed;
    }
    // apply new position
    entity.position = entity.position + dp;
  }
  // dampens infinite bounce
  damp_bounce(entity);
  // for very small velocities
  damp_velocity(entity);
  // reset forces for next step
  entity.force.reset();
  if (entity.type == EntityType::Ball) {
    int b = 0;
  }
}
//
//
//
bool collides(const sf::CircleShape &c1, const sf::CircleShape &c2) {
  // One of the circles has no size
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
//
//
//
bool contains(const sf::CircleShape &big, const sf::CircleShape &small) {
  // get the center points of circles
  sf::Vector2 center_big_circle(big.getPosition().x + big.getRadius(),
                                big.getPosition().y + big.getRadius());
  sf::Vector2 center_small_circle(small.getPosition().x + small.getRadius(),
                                  small.getPosition().y + small.getRadius());

  // distance
  int dist_sq = sqrt(((center_small_circle.x - center_big_circle.x) *
                      (center_small_circle.x - center_big_circle.x)) +
                     ((center_small_circle.y - center_big_circle.y) *
                      (center_small_circle.y - center_big_circle.y)));

  if (big.getRadius() > (dist_sq + small.getRadius())) {
    return true;
  }

  return false;
}
