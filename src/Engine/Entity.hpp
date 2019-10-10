#pragma once
#include "Compass.hpp"
#include "InputDevice.hpp"
#include "Movable.hpp"
#include "Sprite.hpp"
//
//
//
namespace Engine {

/**
 * @brief The Entity class
 */
class Entity {
 public:
  //
  // constructs an enitty without a graphical aspect (default movable)
  //
  Entity();
  //
  //
  //
  Entity(Sprite &in_sprite, Sprite &in_shadow);
  //
  //
  //
  virtual void handleInput();
  //
  //
  //
  virtual void update();
  //
  //
  //
  Direction directionTo(const Entity &in_entity) const;
  //
  //
  //
  void perspectivize(const float in_camera_height) const;
  //
  //
  //
  void attachInput(InputDevice & in_device);
  //
  //
  //
  void detachInput();
  //
  //
  //
  InputDevice *getInput() const;
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

 protected:
  float speed = 1.F;
  InputDevice *input = nullptr;
  bool perspectivizable = true;
};

}  // namespace Engine
