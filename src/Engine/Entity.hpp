#pragma once
#include "Compass.hpp"
#include "Movable.hpp"
#include "Sprite.hpp"
namespace Engine {

/**
 * @brief The Entity class
 */
class Entity {
 public:
  /**
   * @brief Entity
   */
  Entity(Sprite &in_sprite, Sprite& in_shadow);
  /**
   * @brief Entity
   */
  Entity(Movable &in_movable, Sprite &in_sprite, Sprite& in_shadow);
  /**
   * @brief Update
   */
  virtual void Update();
  /**
   * @brief directionTo
   * @param in_entity
   * @return
   */
  Direction directionTo(const Entity &in_entity);
  /**
   * @brief perspectivize
   * @param z
   * @param width
   * @param camera_height
   * @return
   */
  void perspectivize(const float in_camera_height);
  float perspective_width = 0;

  Movable &movable; // if provided from outside
  Movable default_movable; // if just need a genericmovable
  Sprite &sprite;
  Sprite &shadow;
  int shadow_offset = 2;
};

}  // namespace Engine
