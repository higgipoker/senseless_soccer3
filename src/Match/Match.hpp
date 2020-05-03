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
#include "Game/Object.h"
//
#include <SFML/Graphics/RenderTexture.hpp>
//
namespace Senseless {
class Team;
class Player;
enum class TeamType;

// ***************************************************************************
// *                                                                         *
// * Match                                                                   *
// *                                                                         *
// ***************************************************************************
// *
// *
class Match  : public Object{
   public:
    Match(UniquePtr<Pitch> in_pitch,
          Team&            in_home_team,
          Team&            in_away_team,
          BallType         in_ball_type = BallType::Standard);
    ~Match();

    void receive(const MessageName in_message) override;

    const sf::Texture&  getMatchTexture ();
    void                update          ();
    Ball&               getBall         ();
    Team&               getHomeTeam     ();
    Team&               getAwayTeam     ();
    Pitch&              getPitch        () const;
    void                initMatchTexture(   const Texture& team1_texture,
                                            const Texture& team2_texture,
                                            const Texture& ball_texture);
    void                setAttackingTeam(   const TeamType in_which);

    Player* player_in_possession = nullptr;

   protected:
    MatchFactory     factory;
    BallFactory      ball_factory;
    UniquePtr<Pitch> pitch;
    UniquePtr<Ball>  ball;
    Team&            home_team;
    Team&            away_team;
    TeamType         attacking_team;

    static int instances;
};
// *
// *
// ***************************************************************************
}  // namespace Senseless
