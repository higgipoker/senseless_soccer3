#pragma once

#include "Vector.hpp"

namespace Engine {
/**
 * @brief The Movable class
 */
class Movable {
 public:
  /**
   * @brief Movable
   */
  Movable();
  /**
   * @brief step
   */
  void step(float in_dt);

  /// movable elements
  Vector3 position;
  Vector3 velocity;
  Vector3 force;

 private:
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

  /// environment elements
  Vector3 acceleration;
  Vector3 friction;
  Vector3 k1;
  Vector3 k2;
  Vector3 k3;
  Vector3 dp;
  float co_friction = 0;
  float co_air_resistance = 0;
  float co_bounciness = 0;
  float mass = 1;
  float speed = 1;
};
}  // namespace Engine
