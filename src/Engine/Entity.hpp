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
  //
  //
  //
  Entity();
  //
  //
  //
  Entity(Sprite &in_sprite, Sprite &in_shadow);
  //
  //
  //
  virtual void update();
  //
  //
  //
  Direction directionTo(const Entity &in_entity);
  //
  //
  //
  void perspectivize(const float in_camera_height);
  //
  //
  //
  float perspective_width = 0;
  Movable movable;
  Sprite &sprite;
  Sprite &shadow;
  static Sprite dummy_sprite;
  static Sprite dummy_shadow;
  int shadow_offset = 2;
};

}  // namespace Engine
