#pragma once
#include "Movable.hpp"
#include "Sprite.hpp"
#include "Compass.hpp"
namespace Engine {

/**
 * @brief The Entity class
 */
class Entity {
 public:
  /**
   * @brief Entity
   */
  Entity();
  /**
   * @brief directionTo
   * @param in_entity
   * @return
   */
  Direction directionTo(const Entity& in_entity);

  Movable *movable = nullptr;
  Sprite *sprite = nullptr;
  Sprite *shadow = nullptr;
};

}  // namespace Engine
