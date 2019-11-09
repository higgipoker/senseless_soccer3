#pragma once
#include "Ball/Ball.hpp"
//
#include "Ball/BallFactory.hpp"
#include "Engine/Sprite.hpp"
#include "Engine/Texture.hpp"
#include "Engine/Types.hpp"
#include "Match/MatchFactory.hpp"
#include "Pitch/Pitch.hpp"
#include "Team/Team.hpp"
//
#include <SFML/Graphics/RenderTexture.hpp>
//
#include <cassert>
//
//
//
class Match {
 public:
  //
  //
  //
  Match(UniquePtr<Team> in_home_team, UniquePtr<Team> in_away_team,
        BallType in_ball_type = BallType::Standard);
  //
  //
  //
  ~Match() { std::cout << "Destruct Match" << std::endl; }
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
  void setPitch(UniquePtr<Engine::Sprite> in_pitch);
  //
  //
  //
  Ball& getBall();
  //
  //
  //
  inline Team& getHomeTeam() {
    assert(home_team.get());
    return *home_team;
  }
  //
  //
  //
  inline Team& getAwayTeam() {
    assert(away_team.get());
    return *away_team;
  }
  //
  //
  //
  inline Pitch& getPitch() { return static_cast<Pitch&>(*pitch.get()); };
  //
  //
  //
  void initMatchTexture(const Engine::Texture& team1_texture,
                        const Engine::Texture& team2_texture,
                        const Engine::Texture& ball_texture);

  Player* player_in_possession = nullptr;

 protected:
  MatchFactory factory;
  BallFactory ball_factory;
  UniquePtr<Engine::Sprite> pitch;
  UniquePtr<Ball> ball;
  UniquePtr<Team> home_team;
  UniquePtr<Team> away_team;
};
