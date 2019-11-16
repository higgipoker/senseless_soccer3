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
  //
  //
  Entity();
  //
  //
  //
  Entity(UniquePtr<Sprite> in_sprite);
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
  Vector3 directionTo(const Entity &in_entity, bool in_2d = false) const;
  //
  //
  //
  float distanceTo(const Entity &in_entity) const;
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
  bool hasShadow(){
      return has_shadow;
  }

  // has a movable aspect, instead of inheritance
  Movable movable;

 protected:
  UniquePtr<Sprite> sprite;
  UniquePtr<Sprite> shadow;
  bool has_shadow = false;
  int shadow_offset = 2;
  float speed = 1.F;

  // some debug stuff
  static const bool DRAW_RAYS = false;
  sf::RectangleShape xray;
  sf::RectangleShape yray;
};

}  // namespace Engine
