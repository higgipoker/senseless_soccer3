#pragma once
#include "PlayerSprite.hpp"

#include "PlayerStateRun.hpp"
#include "PlayerStateStand.hpp"
#include "PlayerStateDribble.hpp"

#include "Engine/Entity.hpp"
#include "Locomotion/Seek.hpp"

#include <SFML/Graphics/CircleShape.hpp>

class Match;
/**
 * @brief The Player class
 */
class Player : public Engine::Entity {
 public:
  /**
   * @brief Player
   */
  Player(PlayerSprite & in_sprite, PlayerShadowSprite & in_shadow);

  /**
   * @brief Update
   */
  void update();

  /// players know about the match, one match for all players
  static Match *match;

  // test
  void go_to(Engine::Movable &target) {
    locomotion = new Seek(movable, target);
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

  /// represents the players feet for collisions
  sf::CircleShape feet;
  /// represents an area where the ball is under control for dribbling
  sf::CircleShape control;

  // state machine
  PlayerStateStand state_stand;
  PlayerStateRun state_run;
  PlayerStateDribble state_dribble;
  PlayerState *current_state;

  // convenience to avoid casting everywhere
  PlayerSprite &player_sprite;
  PlayerSprite &player_shadow;

  // helper to not clutter up main methods
  void debug();

 public:
  // state machine pattern
  friend class PlayerState;
  friend class PlayerStateStand;
  friend class PlayerStateRun;
  friend class PlayerStateDribble;
};
