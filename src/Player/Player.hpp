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
struct TeamData {
  int shirt_number = 0;
};
struct Attributes {};

//
//
//
enum class RunningSpeed { VerySlow, Slow, Normal, Fast, VeryFast };
//
// running speeds
//
inline std::map<RunningSpeed, float> run_speeds = {
    {RunningSpeed::VerySlow, 0.75F}, {RunningSpeed::Slow, 1.0F},
    {RunningSpeed::Normal, 1.5F},    {RunningSpeed::Fast, 2.0F},
    {RunningSpeed::VeryFast, 2.5F},
};
//
// dribbling speeds
//
inline std::map<RunningSpeed, float> dribble_speeds = {
    {RunningSpeed::VerySlow, 0.25F}, {RunningSpeed::Slow, 0.5F},
    {RunningSpeed::Normal, 1.0F},    {RunningSpeed::Fast, 1.5F},
    {RunningSpeed::VeryFast, 2.0F},
};
//
// dribble knock on forces
//
inline std::map<RunningSpeed, float> kick_mods = {
    {RunningSpeed::VerySlow, 0.8F}, {RunningSpeed::Slow, 1.2F},
    {RunningSpeed::Normal, 1.4F},   {RunningSpeed::Fast, 2.3F},
    {RunningSpeed::VeryFast, 3.0F},
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
  Player(std::unique_ptr<PlayerSprite> in_sprite,
         std::unique_ptr<PlayerSprite> in_shadow);
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
  void setTeamData(TeamData in_data);
  //
  //
  //
  void pass(Engine::Vector3 in_force);
  //
  //
  //
  void pass(Player &in_receiver);
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
  Engine::Compass getDirection();
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
  RunningSpeed speed = RunningSpeed::Normal;
  // team stuff
  TeamData team_data;
  // playing attributes
  Attributes attribs;
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
