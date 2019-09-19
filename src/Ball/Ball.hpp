#pragma once

#include "Engine/Entity.hpp"

/**
 * @brief The Ball class
 */
class Ball : public Engine::Entity {
 public:
  /**
   * @brief Ball
   */
  Ball();

  /**
   * @brief Update
   */
  void update();

 protected:
};
