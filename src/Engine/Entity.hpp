#pragma once
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
  Entity();

  Movable *movable = nullptr;
  Sprite *sprite = nullptr;
  Sprite *shadow = nullptr;
};

}  // namespace Engine
