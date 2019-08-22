#include "ball.hpp"
#include "../globals.hpp"

#include <gamelib3/math/vector.hpp>

#include <iostream>

using namespace gamelib3;
namespace senseless_soccer3 {

const float CLAMP_INF_BOUNCE = 0.01f;

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
Ball::Ball() {}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void Ball::Step(float dt) {
  if (collide_ground()) {
    bounce();
  } else {
    // either gravity or friction
    if (in_air()) {
      apply_gravity(dt);
      apply_drag(dt);
    } else {
      apply_friction();
    }
    apply_spin();
    decay_spin();
    integrate_improved_euler(dt);
  }
  collidable.setPosition(position.x, position.y);
  force.reset();
  forces.reset();
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void Ball::applyForce(gamelib3::Vector3 _force) { force += force; }

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
bool Ball::collide_ground() {
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
void Ball::bounce() {
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
void Ball::apply_gravity(float dt) {
  forces.gravity.z = -environment.gravity;
  force += forces.gravity * mass * dt;
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void Ball::apply_friction() {
  forces.friction.x = environment.co_friction;
  forces.friction.y = environment.co_friction;
  forces.friction.z = 0;
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void Ball::apply_spin() {
  force += forces.sidespin;
  force += forces.topspin;
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void Ball::decay_spin() {
  if (Floats::greater_than(forces.topspin.magnitude(), 0)) {
    forces.topspin = forces.topspin * environment.co_spin_decay;
  } else {
    forces.topspin.reset();
  }
  if (Floats::greater_than(forces.sidespin.magnitude(), 0)) {
    forces.sidespin = forces.sidespin * environment.co_spin_decay;
  } else {
    forces.sidespin.reset();
  }
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void Ball::apply_drag(float dt) {
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
void Ball::clamp_to_ground() {
  if (Floats::less_than(position.z, 0)) {
    position.z = 0;
    velocity.z = 0;
  }
}

// -----------------------------------------------------------------------------
// addSideSpin
// -----------------------------------------------------------------------------
void Ball::addSideSpin(const Vector3 &s) { forces.sidespin += s; }

// -----------------------------------------------------------------------------
// addTopSpin
// -----------------------------------------------------------------------------
void Ball::addTopSpin(const Vector3 &s) { forces.topspin += s; }

// -----------------------------------------------------------------------------
// rebound
// -----------------------------------------------------------------------------
void Ball::rebound(Vector3 &wall, const Vector3 dampen) {
  wall = wall.normalise();
  velocity *= dampen;
  velocity = velocity.reflect(wall);
  position += velocity * 0.01f;  // tmp fixes sticky walls
}

// -----------------------------------------------------------------------------
// perspectivize
// -----------------------------------------------------------------------------
void Ball::perspectivize(float camera_height) {
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
