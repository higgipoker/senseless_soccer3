#pragma once
#include "PlayerSprite.hpp"
#include "PlayerStateDribble.hpp"
#include "PlayerStateRun.hpp"
#include "PlayerStateStand.hpp"

#include "Brain/Brain.hpp"
#include "Engine/Entity.hpp"

#include <SFML/Graphics/CircleShape.hpp>

#include <map>
//
//
//
enum class PlayerSpeed : int {
  VerySlow = 1,
  Slow = 2,
  Normal = 3,
  Fast = 4,
  VeryFast = 5
};
//
// running speeds
//
inline std::map<PlayerSpeed, float> run_speeds = {
    {PlayerSpeed::VerySlow, 0.75F}, {PlayerSpeed::Slow, 1.0F},
    {PlayerSpeed::Normal, 1.5F},    {PlayerSpeed::Fast, 2.0F},
    {PlayerSpeed::VeryFast, 2.5F},
};
//
// dribbling speeds
//
inline std::map<PlayerSpeed, float> dribble_speeds = {
    {PlayerSpeed::VerySlow, 0.25F}, {PlayerSpeed::Slow, 0.5F},
    {PlayerSpeed::Normal, 1.0F},    {PlayerSpeed::Fast, 1.5F},
    {PlayerSpeed::VeryFast, 2.0F},
};
//
// dribble knock on forces
//
inline std::map<PlayerSpeed, float> kick_mods = {
    {PlayerSpeed::VerySlow, 0.8F}, {PlayerSpeed::Slow, 1.2F},
    {PlayerSpeed::Normal, 1.4F},   {PlayerSpeed::Fast, 2.3F},
    {PlayerSpeed::VeryFast, 3.0F},
};

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
  void run(Engine::Compass in_direction);
  //
  //
  //
  void run(Engine::Vector3 in_direction);
  //
  //
  //
  void stopRunning();
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
  // speed attrib
  PlayerSpeed spd = PlayerSpeed::Normal;
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
