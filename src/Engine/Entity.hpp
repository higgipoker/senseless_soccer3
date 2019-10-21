#pragma once
#include "Compass.hpp"
#include "InputDevice.hpp"
#include "Movable.hpp"
#include "Sprite.hpp"
#include "Types.hpp"
//
//
//
namespace Engine {

/**
 * @brief The Entity class
 */
class Entity : public InputListener{
 public:
  //
  // constructs an enitty without a graphical aspect (default movable)
  //
  Entity();
  //
  //
  //
  Entity(UnqPtr<Sprite> in_sprite, UnqPtr<Sprite> in_shadow);
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
  Vector3 directionTo(const Entity &in_entity) const;
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
  Sprite &getSprite();
  //
  //
  //
  Sprite &getShadow();
  //
  //
  //
  bool isInputAttached();
  //
  //
  //
  InputDevice & getInputDevice() const;
  // has a movable aspect, instead of inheritance
  Movable movable;
  //
  // inputlistener interface implementation
  //
  void onEvent(const InputEvent in_event,
                       const std::vector<int> &in_params) override{};

 protected:
  UnqPtr<Sprite> sprite;
  UnqPtr<Sprite> shadow;
  int shadow_offset = 2;
  float speed = 1.F;
  InputDevice *input = nullptr;
};

}  // namespace Engine
