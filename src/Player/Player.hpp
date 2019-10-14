#pragma once
#include "PlayerSprite.hpp"
#include "PlayerStateDribble.hpp"
#include "PlayerStateRun.hpp"
#include "PlayerStateStand.hpp"

#include "Brain/Brain.hpp"
#include "Engine/Entity.hpp"

#include <SFML/Graphics/CircleShape.hpp>

class Match;
//
//
//
class Player : public Engine::Entity {
 public:
  //
  //
  //
  Player(PlayerSprite &in_sprite, PlayerShadowSprite &in_shadow);
  //
  //
  //
  void handleInput() override;
  //
  //
  //
  void update() override;
  //
  //
  //
  Engine::Compass direction();
  //
  //
  //
  Brain &getBrain();
  //
  //
  //
  static void connectMatch(Match &in_match);
  //
  //
  //
  static Match &getMatch();
  //
  //
  //
  bool ballInControlRange();

 protected:
  //
  //
  //
  // players know about the match, one match for all players
  static Match *match;
  // a player has a brain (well, most do)
  Brain brain;
  // track if the ball is under control
  bool ball_under_control = false;
  // currently facing direction
  Engine::Compass facing;
  // represents the players feet for collisions
  sf::CircleShape feet;
  // represents an area where the ball is under control for dribbling
  sf::CircleShape control;
  // state machine
  PlayerStateStand state_stand;
  PlayerStateRun state_run;
  PlayerStateDribble state_dribble;
  PlayerState *state;
  // convenience to avoid casting everywhere
  PlayerSprite &player_sprite;
  PlayerSprite &player_shadow;
  //
  //
  //
  void face_ball();
  //
  //
  //
  void change_state(const player_state in_state);
  //
  //
  //
  void debug();

 public:
  // state machine pattern
  friend class PlayerState;
  friend class PlayerStateStand;
  friend class PlayerStateRun;
  friend class PlayerStateDribble;
  friend class BrainDribble;
  friend class BrainRetrieve;
};
