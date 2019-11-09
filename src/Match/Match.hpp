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
  Match(Team &in_home_team, Team &in_away_team,
        BallType in_ball_type = BallType::Standard);
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
    return home_team;
  }
  //
  //
  //
  inline Team& getAwayTeam() {
    return away_team;
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
 protected:
  MatchFactory factory;
  BallFactory ball_factory;
  UniquePtr<Engine::Sprite> pitch;
  UniquePtr<Ball> ball;
  Team &home_team;
  Team &away_team;
};
