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
  void attachInput(InputDevice &in_device);
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
  Movable movable;
  Sprite &sprite;
  Sprite &shadow;
  int shadow_offset = 2;
  static Sprite dummy_sprite;
  static Sprite dummy_shadow;

 protected:
  float speed = 1.F;
  InputDevice *input = nullptr;
};

}  // namespace Engine
