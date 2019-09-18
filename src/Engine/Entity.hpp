#pragma once
#include "Sprite.hpp"
#include "Movable.hpp"
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
};

}  // namespace Engine
