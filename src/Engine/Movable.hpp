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
  Movable();
  //
  //
  //
  const Vector3 getPosition() const;
  void setPosition(const Vector3 &in_position);
  void setPosition(const float in_x, const float in_y, const float in_z);
  void setPosition(const float in_x, const float in_y);
  void move(float in_dx, float in_dy);
  float getX()const;
  float getY()const;
  float getZ()const;
  void setX(float in_x);
  void setY(float in_y);
  void setZ(float in_z);
  void resetVelocity();
  //
  //
  //
  const Vector3 getVelocity()const;
  float getVelocityMag(bool in_2d = false);
  void setVelocity(const Vector3 &in_velocity);
  void normalizeVelocity(bool in_2d = false);
  //
  //
  //
  void applyForce(Vector3 in_force);
  //
  //
  //
  void resetForces();
  //
  //
  //
  void step(float in_dt);
  //
  //
  //
  void toggleGravity(bool in_status);

  /// environment elements TODO struct
  float co_friction = 0;
  float co_air_resistance = 0;
  float co_bounciness = 0;
  float mass = 1;
  float speed = 1;

 protected:
  /// movable components
  Vector3 position;
  Vector3 velocity;
  Vector3 force;
  /**
   * @brief integrate
   * @param in_dt
   */
  void integrate_improved_euler(const float in_dt);
  /**
   * @brief integrate
   * @param in_dt
   */
  Vector3 integrate(const float in_dt);
  /**
   * @brief bounce
   */
  void bounce();
  /**
   * @brief damp_bounce
   */
  void damp_bounce();
  /**
   * @brief damp_velocity
   */
  void damp_velocity();

  // tmp hack
  bool affected_by_gravity = true;
};
}  // namespace Engine
