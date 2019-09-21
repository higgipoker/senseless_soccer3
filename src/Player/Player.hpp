#pragma once
#include "PlayerSprite.hpp"

#include "PlayerStateRun.hpp"
#include "PlayerStateStand.hpp"

#include "Engine/Entity.hpp"
#include "Locomotion/Seek.hpp"

class Match;
/**
 * @brief The Player class
 */
class Player : public Engine::Entity {
 public:
  /**
   * @brief Player
   */
  Player(PlayerSprite *in_sprite, PlayerShadowSprite *in_shadow);

  /**
   * @brief Update
   */
  void update();

  /// players know about the match, one match for all players
  static Match *match;

  /// entity aspects
  Engine::Movable player_movable;
  PlayerSprite *player_sprite = nullptr;
  PlayerSprite *player_shadow = nullptr;

  // test
  void go_to(Engine::Movable &target) {
    locomotion = new Seek(*this->movable, target);
    locomotion->start();
  }
  Seek *locomotion = nullptr;

 protected:
  /**
   * @brief face_ball
   */
  void face_ball();
  /**
   * @brief change_state
   * @param in_state
   */
  void change_state(const player_state in_state);

  /// currently facing direction
  Engine::Direction facing;

  PlayerStateStand state_stand;
  PlayerStateRun state_run;
  PlayerState *current_state;



 public:
  // state machine pattern
  friend class PlayerState;
  friend class PlayerStateStand;
  friend class PlayerStateRun;
  friend class PlayerStateDribble;
};
