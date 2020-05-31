#pragma once
#include "Gameplan.hpp"
#include "KitFactory.hpp"
#include "PlayingPosition.hpp"
//
#include "Player/PlayerFactory.hpp"
//
#include "Engine/InputDevice.hpp"
#include "Engine/Sprite.hpp"
#include "Engine/Texture.hpp"
#include <memory>
//
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Texture.hpp>
//
#include <memory>
#include <vector>
namespace Senseless {
//
//
//
enum class TeamStrip { Home, Away };
enum class AttackingState { Attacking, Defending };
//
//
//
class Match;
class Player;
//
//
//
class Team {
 public:
                        Team                    (const std::string& in_name, const TeamStrip in_home_or_away, const Kit& in_kit);
                        ~Team                   ();
  void                  setAttackingGoal        (Direction in_dir);
  void                  update                  ();
  void                  addDefaultPlayers       (Team &in_other_team);
  void                  addPlayer               (Player *in_player);
  bool                  hasPlayers              () { return !players.empty(); }
  void                  setMatch                (Match& in_match);
  void                  setAttackingState       (const AttackingState in_state);
  void                  goToSetPiecePositions   (const Situation in_situation, const Direction in_pitch_side = Direction::West);
  Player&               getPlayer               (const size_t in_which);
  size_t                numberPlayers           () { return players.size(); }
  TeamStrip              getTeamType             () { return home_or_away; }
  Direction             getAttackingGoal        () const;
  Direction             getDefendingGoal        () const;
  AttackingState        getAttackingState       () const;
  std::unique_ptr<Texture>    getSpriteTexture();
  std::unique_ptr<Texture>    getShadowTexture        ();
  std::vector<Vector3>  getPlayerPositions      ();

  Gameplan      gameplan;
  Sprite        sprite;
  std::string   name;
  Player*       closest_to_ball = nullptr;

 protected:
  Match*                            match = nullptr;
  AttackingState                    attacking_state = AttackingState::Attacking;
  TeamStrip                          home_or_away = TeamStrip::Home;
  Kit                               kit;
  std::vector<Player*>              players;
  int                               loose_ball_ticks = 60;
  Vector3                           last_ball_position;  
  Direction                         attacking_goal = Direction::South;
  Direction                         defending_goal = Direction::North;
  std::unique_ptr<Texture>                sprite_texture = std::make_unique<Texture>();
  std::unique_ptr<Texture>                shadow_texture = std::make_unique<Texture>();

  // debugs
  sf::RectangleShape    defensive_line;
  static int            instances;

 public:
  friend class Player;
};
}  // namespace Senseless
