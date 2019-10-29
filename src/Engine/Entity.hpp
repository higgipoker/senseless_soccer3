#pragma once
#include "Compass.hpp"
#include "InputDevice.hpp"
#include "Movable.hpp"
#include "Sprite.hpp"
#include "Types.hpp"

#include <SFML/Graphics/RectangleShape.hpp>
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
  Entity(UniquePtr<Sprite> in_sprite, UniquePtr<Sprite> in_shadow);
  //
  //
  //
  virtual void handleInput();
  //
  //
  //
  virtual void update(const float in_dt);
  //
  //
  //
  Vector3 directionTo(const Entity &in_entity, bool in_2d =false) const;
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
  void onInputEvent(const InputEvent in_event,
                       const std::vector<int> &in_params) override{};

 protected:
  UniquePtr<Sprite> sprite;
  UniquePtr<Sprite> shadow;
  int shadow_offset = 2;
  float speed = 1.F;
  InputDevice *input = nullptr;

  // some debug stuff
  static const bool DRAW_RAYS = true;
  sf::RectangleShape xray;
  sf::RectangleShape yray;
};

}  // namespace Engine
