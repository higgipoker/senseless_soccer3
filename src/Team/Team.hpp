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
#include "Engine/Types.hpp"
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
enum class TeamType { Home, Away };
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
                        Team                    (const std::string& in_name, const TeamType in_home_or_away, const Kit& in_kit);
                        ~Team                   ();
  void                  setAttackingGoal        (Direction in_dir);
  void                  update                  ();
  void                  addDefaultPlayers       (const Team& in_other_team);
  void                  addPlayer               (UniquePtr<Player> in_player);
  bool                  hasPlayers              () { return !players.empty(); }
  void                  setMatch                (Match& in_match);
  void                  setAttackingState       (const AttackingState in_state);
  void                  goToSetPiecePositions   (const Situation in_situation, const Direction in_pitch_side = Direction::West);
  Player&               getPlayer               (const size_t in_which);
  size_t                numberPlayers           () { return players.size(); }
  TeamType              getTeamType             () { return home_or_away; }
  Direction             getAttackingGoal        () const;
  Direction             getDefendingGoal        () const;
  AttackingState        getAttackingState       () const;
  UniquePtr<Texture> getSpriteTexture();
  UniquePtr<Texture>    getShadowTexture        ();
  std::vector<Vector3>  getPlayerPositions      ();

  Gameplan      gameplan;
  Sprite        sprite;
  std::string   name;
  Player*       closest_to_ball = nullptr;

 protected:
  Match*                            match = nullptr;
  AttackingState                    attacking_state = AttackingState::Attacking;
  TeamType                          home_or_away = TeamType::Home;
  Kit                               kit;
  std::vector<UniquePtr<Player>>    players;
  int                               loose_ball_ticks = 60;
  Vector3                           last_ball_position;
  PlayerFactory                     player_factory;
  Direction                         attacking_goal = Direction::South;
  Direction                         defending_goal = Direction::North;
  UniquePtr<Texture>                sprite_texture = std::make_unique<Texture>();
  UniquePtr<Texture>                shadow_texture = std::make_unique<Texture>();

  // debugs
  sf::RectangleShape    defensive_line;
  static int            instances;

 public:
  friend class Player;
};
}  // namespace Senseless
