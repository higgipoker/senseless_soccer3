#pragma once
#include "MatchFactory.hpp"
//
#include "Ball/Ball.hpp"
#include "Pitch/Pitch.hpp"
//
#include "Ball/BallFactory.hpp"
#include "Engine/Sprite.hpp"
#include "Engine/Texture.hpp"
#include "Engine/Types.hpp"
//
#include <SFML/Graphics/RenderTexture.hpp>
//
namespace Senseless {
class Team;
class Player;
enum class TeamType;
//
//
//
class Match {
 public:
  //
  //
  //
  Match(UniquePtr<Pitch> in_pitch, Team& in_home_team, Team& in_away_team,
        BallType in_ball_type = BallType::Standard);
  //
  //
  //
  ~Match();
  //
  //
  //
  const sf::Texture& getMatchTexture() { return factory.getMatchTexture(); }
  //
  //
  //
  void update();
  //
  //
  //
  Ball& getBall();
  //
  //
  //
  inline Team& getHomeTeam() { return home_team; }
  //
  //
  //
  inline Team& getAwayTeam() { return away_team; }
  //
  //
  //
  inline Pitch& getPitch() const { return *pitch.get(); };
  //
  //
  //
  void initMatchTexture(const Texture& team1_texture,
                        const Texture& team2_texture,
                        const Texture& ball_texture);
  //
  //
  //
  void setAttackingTeam(const TeamType in_which);

  // todo tmp
  Player* player_in_possession = nullptr;

 protected:
  MatchFactory factory;
  BallFactory ball_factory;
  UniquePtr<Pitch> pitch;
  UniquePtr<Ball> ball;
  Team& home_team;
  Team& away_team;
  TeamType attacking_team;

  static int instances;
};
}  // namespace Senseless
