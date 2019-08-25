#include "ball_movable.hpp"
#include "../globals.hpp"

#include <gamelib3/math/vector.hpp>

#include <iostream>

using namespace gamelib3;
namespace senseless_soccer3 {

const float CLAMP_INF_BOUNCE = 0.001f;

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
BallMovable::BallMovable() {
  collidable.setRadius(2);
  width = collidable.getRadius() * 2;
  co_friction = 0.1f;
  // position.z = 19;
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void BallMovable::Step(float dt) {
  bool need_friction = false;
  if (collide_ground()) {
    bounce();
  } else {
    // either gravity or friction
    if (in_air()) {
      apply_gravity(dt);
      apply_drag(dt);
    } else {
      need_friction = true;
    }
    apply_spin();
    decay_spin();
    // step 1
    if (velocity.magnitude2d()) {
      bool vr = true;
    }
    if (need_friction) {
      velocity = (velocity.multiply2d(co_friction));
    }
    Vector3 acceleration = force / mass;
    Vector3 k1 = acceleration * dt;

    // step 2
    if (need_friction)
      velocity = (velocity - (velocity + k1).multiply2d(co_friction));
    acceleration = force / mass;
    Vector3 k2 = acceleration * dt;

    // update velocity
    velocity = velocity + (k1 + k2) / 2;

    // change in position (converted to pixels)
    Vector3 dp = (velocity * dt);

    // apply new position
    position = position + dp;

    force.reset();
  }
  collidable.setPosition(position.x, position.y);
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void BallMovable::applyForce(gamelib3::Vector3 _force) { force += force; }

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
bool BallMovable::collide_ground() {
  // moving down
  if (Floats::less_than(velocity.z, 0)) {
    // touched ground
    if (Floats::less_than(position.z, 0)) {
      return true;
    }
  }
  return false;
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void BallMovable::bounce() {
  position.z = 0;
  if (Floats::abs_less_than(velocity.z, CLAMP_INF_BOUNCE)) {
    velocity.z = 0;
  } else {
    velocity.z = -velocity.z;
    velocity.z *= environment.co_bounciness;
  }
}

// -----------------------------------------------------------------------------
// apply_gravity
// -----------------------------------------------------------------------------
void BallMovable::apply_gravity(float dt) {
  forces.gravity.z = -environment.gravity * dt;
  force += forces.gravity * mass * dt;
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void BallMovable::apply_spin() {
  if (forces.topspin.y) {
    force += forces.sidespin;
  }
  if (forces.sidespin.x) {
    force += forces.topspin;
  }
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void BallMovable::decay_spin() {
  if (forces.topspin.y) {
    forces.topspin = forces.topspin * environment.co_spin_decay;
  }
  if (forces.sidespin.x) {
    forces.sidespin = forces.sidespin * environment.co_spin_decay;
  }
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void BallMovable::apply_drag(float dt) {
  // drag = (air density * co_drag * cross section area) / 2
  // in the opposite direction to velocity
  Vector3 dir = velocity.reverse().normalise();
  forces.drag =
      dir * (environment.co_drag *
             (PI * collidable.getRadius() * collidable.getRadius()) / 2);
  force += forces.drag * dt;
}

// -----------------------------------------------------------------------------
// clamp_to_ground
// -----------------------------------------------------------------------------
void BallMovable::clamp_to_ground() {
  if (Floats::less_than(position.z, 0)) {
    position.z = 0;
    velocity.z = 0;
  }
}

// -----------------------------------------------------------------------------
// addSideSpin
// -----------------------------------------------------------------------------
void BallMovable::addSideSpin(const Vector3 &s) { forces.sidespin += s; }

// -----------------------------------------------------------------------------
// addTopSpin
// -----------------------------------------------------------------------------
void BallMovable::addTopSpin(const Vector3 &s) { forces.topspin += s; }

// -----------------------------------------------------------------------------
// rebound
// -----------------------------------------------------------------------------
void BallMovable::rebound(Vector3 &wall, const Vector3 dampen) {
  wall = wall.normalise();
  velocity *= dampen;
  velocity = velocity.reflect(wall);
  position += velocity * 0.01f;  // tmp fixes sticky walls
}

// -----------------------------------------------------------------------------
// perspectivize
// -----------------------------------------------------------------------------
void BallMovable::perspectivize(float camera_height) {
  // size depending on distance from camera
  //  float dimensions = collidable.getRadius() * 2;
  //  float dist_from_camera = camera_height - position.z;
  //  float angular_diameter = 2 * (atanf(dimensions / (2 * dist_from_camera)));
  //  float degs = DEGREES(angular_diameter);
  //  float sprite_scale_factor = degs / dimensions;

  //  // TODO
  //  float sprite_ratio = dimensions / entity.renderable.entity.image_width;
  //  entity.renderable.entity.sprite_scale_factor *= sprite_ratio;
  //  entity.renderable.entity.sprite.scale(sprite_scale_factor,
  //                                        sprite_scale_factor);

  //  // y offset due to height
  //  float z_cm = position.z * CM_PER_PIXEL;

  //  if (Floats::greater_than(z_cm, 0)) {
  //    float y_offset = Y_OFFSET_DUE_TO_HEIGHT * z_cm;
  //    entity.renderable.entity.sprite.move(0, -y_offset);
  //  }
}
}  // namespace senseless_soccer3
