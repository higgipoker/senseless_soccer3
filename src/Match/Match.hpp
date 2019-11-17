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
class Team;
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
    const sf::Texture& getMatchTexture() {
        return factory.getMatchTexture();
    }
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
    inline Pitch& getPitch() const {
        return *pitch.get();
    };
    //
    //
    //
    void initMatchTexture(const Engine::Texture& team1_texture, const Engine::Texture& team2_texture,
                          const Engine::Texture& ball_texture);

   protected:
    MatchFactory factory;
    BallFactory ball_factory;
    UniquePtr<Pitch> pitch;
    UniquePtr<Ball> ball;
    Team& home_team;
    Team& away_team;

    static int instances;
};
