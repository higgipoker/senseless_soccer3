#pragma once

#include <gamelib3/engine/engine.hpp>
#include <gamelib3/math/vector.hpp>
#include <gamelib3/physics/movable.hpp>

namespace senseless_soccer3 {

class Ball : public gamelib3::Movable {
 public:
  /**
   * @brief Ball
   */
  Ball();

  /**
   * @brief accumulate_forces
   * @param dt
   */
  virtual void Step(float dt) override;

  /**
   * @brief applyForce
   * @param force
   */
  void applyForce(gamelib3::Vector3 _force);

  /**
   * @brief rebound
   * @param wall
   * @param dampen
   */
  void rebound(gamelib3::Vector3 &wall,
               const gamelib3::Vector3 dampen = gamelib3::Vector3(1, 1, 1));

  /**
   * @brief addSideSpin
   * @param s
   */
  void addSideSpin(const gamelib3::Vector3 &s);

  /**
   * @brief addTopSpin
   * @param s
   */
  void addTopSpin(const gamelib3::Vector3 &s);

 private:
  sf::CircleShape collidable;

  /**
   * @brief integrate
   * @param dt
   */
  void integrate(float dt);
  /**
   * @brief collide_ground
   * @return
   */
  bool collide_ground(void);

  /**
   * @brief bounce
   */
  void bounce();

  /**
   * @brief apply_gravity
   * @param dt
   */
  void apply_gravity(float dt);

  /**
   * @brief apply_friction
   */
  void apply_friction();

  /**
   * @brief apply_spin
   */
  void apply_spin();

  /**
   * @brief decay_spin
   */
  void decay_spin();

  /**
   * @brief apply_drag
   */
  void apply_drag(float dt);

  /**
   * @brief clamp_to_ground
   */
  void clamp_to_ground(void);

  /**
   * @brief perspectivize
   * @param camera_height
   */
  void perspectivize(float camera_height);

  /**
   * @brief in_air
   * @return
   */
  inline bool in_air() { return gamelib3::Floats::greater_than(position.z, 0); }

  // ball environment for physics
  struct {
    float gravity = 9.8f;
    float air_density = 1.0f;
    float co_drag = 0.9f;
    float co_friction = 0.01f;
    float co_friction_bounce = 0.9f;
    float co_bounciness = 0.9f;
    float co_spin_decay = 0.8f;
  } environment;

  struct {
    void reset() {
      drag.reset();
      topspin.reset();
      sidespin.reset();
      friction.reset();
    }
    gamelib3::Vector3 drag;
    gamelib3::Vector3 topspin;
    gamelib3::Vector3 sidespin;
    gamelib3::Vector3 friction;
    gamelib3::Vector3 gravity{0.0f, 0.0f, 9.8f};

  } forces;
};

}  // namespace senseless_soccer3
