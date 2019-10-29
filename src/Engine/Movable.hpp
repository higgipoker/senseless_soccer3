#pragma once

#include "Vector.hpp"

namespace Engine {
//
//
//
class Movable {
 public:
  //
  //
  //
  void setPosition(const float in_x, const float in_y, const float in_z);
  //
  //
  //
  void setPosition(const float in_x, const float in_y);
  //
  //
  //
  void setPosition(const int in_x, const int in_y);
  //
  //
  //
  void move(const float in_dx, const float in_dy);
  //
  //
  //
  void resetVelocity();
  //
  //
  //
  void place(const Vector3& in_position);
  //
  //
  //
  void applyForce(const Vector3& in_force);
  //
  //
  //
  void resetForces();
  //
  //
  //
  void step(const float in_dt);
  //
  //
  //
  void toggleGravity(const bool in_status);

  /// object physical properties
  struct {
    float mass = 1;
    float co_bounciness = 0;
    float co_friction = 0;
    float co_air_resistance = 0;
    float co_spin_decay = 0.8F;
    float cross_section = 0;
  } properties;

  /// environment elements
  struct {
    float air_density = 1.0F;
  } environment;

  // outside influences
  struct {
    Vector3 sidespin;
    Vector3 topspin;
    Vector3 force;

    void reset() { force.reset(); }
  } forces;

  /// movable components
  Vector3 position;
  Vector3 velocity;

 private:
  //
  //
  //
  void integrate_improved_euler(const float in_dt);
  //
  //
  //
  Vector3 integrate(const float in_dt);
  //
  //
  //
  bool affected_by_gravity = true;
};
}  // namespace Engine
