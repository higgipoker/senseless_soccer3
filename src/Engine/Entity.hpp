#pragma once
#include "Compass.hpp"
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
class Entity {
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
  virtual void update();
  //
  //
  //
  Vector3 directionTo(const Entity &in_entity, bool in_2d =false) const;
  //
  //
  //
  Sprite &getSprite();
  //
  //
  //
  Sprite &getShadow();

  // has a movable aspect, instead of inheritance
  Movable movable;

 protected:
  UniquePtr<Sprite> sprite;
  UniquePtr<Sprite> shadow;
  int shadow_offset = 2;
  float speed = 1.F;

  // some debug stuff
  static const bool DRAW_RAYS = true;
  sf::RectangleShape xray;
  sf::RectangleShape yray;
};

}  // namespace Engine
