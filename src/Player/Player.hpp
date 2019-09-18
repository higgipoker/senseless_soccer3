#pragma once
#include "PlayerSprite.hpp"

#include "Engine/Entity.hpp"

/**
 * @brief The Player class
 */
class Player : public Engine::Entity {
 public:
  /**
   * @brief Player
   */
  Player();

  PlayerSprite *player_sprite = nullptr;

  // tmp test
  void animate(PlayerAnimationType in_type, Engine::Direction in_dir) {
    if (player_sprite = static_cast<PlayerSprite *>(sprite)) {
      player_sprite->setAnimation(in_type, in_dir);
    }
  }
};
