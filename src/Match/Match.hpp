#pragma once
#include "MatchFactory.hpp"
//
#include "Ball/Ball.hpp"
#include "Pitch/Pitch.hpp"
//
#include "Ball/BallFactory.hpp"
#include "Engine/Sprite.hpp"
#include "Engine/Texture.hpp"
#include <memory>
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
class Match : public Object{
   public:
    Match   (     Pitch&           in_pitch,
                  Team&            in_home_team,
                  Team&            in_away_team,
                  BallType         in_ball_type = BallType::Standard);
    ~Match  ();

    // object message receiver
    void                receive         (const MessageName in_message) override;

    void                step            ();
    const sf::Texture&  getMatchTexture ();    
    Ball&               getBall         ();
    Team&               getHomeTeam     ();
    Team&               getAwayTeam     ();
    Pitch&              getPitch        () const;
    void                setAttackingTeam(   const TeamStrip in_which);
    void                initMatchTexture(   const Texture& team1_texture,
                                            const Texture& team2_texture,
                                            const Texture& ball_texture);
    void                setBall         (Ball &in_ball);

    Player* player_in_possession = nullptr;

   protected:
    MatchFactory     factory;
    BallFactory      ball_factory;
    Pitch&           pitch;    
    Team&            home_team;
    Team&            away_team;
    Ball*            ball = nullptr;
    TeamStrip        attacking_team;

    // debug checking for mem leakst
    static int instances;
};

}  // namespace Senseless
