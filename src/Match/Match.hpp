#pragma once
#include "MatchFactory.hpp"
//
#include "Ball/Ball.hpp"
#include "Pitch/Pitch.hpp"
//
#include <memory>

#include "Team/KitFactory.hpp"
#include "Ball/BallFactory.hpp"
#include "Engine/Entity.hpp"
#include "Engine/Sprite.hpp"
#include "Engine/Texture.hpp"
#include "Team/Team.hpp"
#include "Game/Object.h"
//
#include <SFML/Graphics/RenderTexture.hpp>
//
namespace Senseless {
class Team;
class Player;
enum class TeamStrip;

// ***************************************************************************
// *                                                                         *
// * Match                                                                   *
// *                                                                         *
// ***************************************************************************
class Match : public Entity {
 public:
  Match(const Kit &in_home_kit,
        const Kit &in_away_kit);
  ~Match();

  void step();
  const sf::Texture& getMatchTexture();
  Team& getHomeTeam(){return *home_team;}
  Team& getAwayTeam(){return *away_team;}
  void setAttackingTeam(const TeamStrip in_which);

  Player* player_in_possession = nullptr;

 protected:
  std::unique_ptr<Team> home_team;
  std::unique_ptr<Team> away_team;
  std::unique_ptr<sf::RenderTexture> match_texture;

  // debug checking for mem leakst
  static int instances;
};

}  // namespace Senseless
