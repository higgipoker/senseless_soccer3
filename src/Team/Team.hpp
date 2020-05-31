#pragma once
#include "Gameplan.hpp"
#include "KitFactory.hpp"
#include "PlayingPosition.hpp"
//
#include "Player/PlayerFactory.hpp"
//
#include <memory>

#include "Engine/InputDevice.hpp"
#include "Engine/Sprite.hpp"
#include "Engine/Texture.hpp"
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
class Team : public Entity {
 public:
  Team(const std::string& in_name);
  ~Team();
  void setAttackingGoal(Direction in_dir);
  void update(const float in_dt) override;
  void addDefaultPlayers(Team& in_other_team);
  void addPlayer(Player* in_player);
  bool hasPlayers() { return !players.empty(); }
  void setAttackingState(const AttackingState in_state);
  void goToSetPiecePositions(const Situation in_situation,
                             const Direction in_pitch_side = Direction::West);
  size_t numberPlayers() { return players.size(); }
  Direction getAttackingGoal() const;
  Direction getDefendingGoal() const;
  AttackingState getAttackingState() const;
  std::vector<Vector3> getPlayerPositions();

  std::vector<Player*> players;

  Gameplan gameplan;
  Sprite sprite;
  std::string name;
  Player* closest_to_ball = nullptr;

 protected:
  AttackingState attacking_state = AttackingState::Attacking;
  TeamStrip home_or_away = TeamStrip::Home;
  int loose_ball_ticks = 60;
  Vector3 last_ball_position;
  Direction attacking_goal = Direction::South;
  Direction defending_goal = Direction::North;

  // debugs
  sf::RectangleShape defensive_line;
  static int instances;

 public:
  friend class Player;
};
}  // namespace Senseless
