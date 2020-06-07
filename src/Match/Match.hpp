#pragma once
#include "MatchFactory.hpp"
//
#include "Ball/Ball.hpp"
#include "Pitch/Pitch.hpp"
//
#include <memory>

#include "Ball/Ball.hpp"
#include "Ball/BallFactory.hpp"
#include "Engine/Camera.hpp"
#include "Engine/Entity.hpp"
#include "Engine/Sprite.hpp"
#include "Engine/Texture.hpp"
#include "Game/Object.h"
#include "Pitch/MiniMap.hpp"
#include "Pitch/Pitch.hpp"
#include "Team/KitFactory.hpp"
#include "Team/Team.hpp"
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
    Match(float in_window_width, float in_window_height, const Kit &in_home_kit,
          const Kit &in_away_kit);
    ~Match();

    void step();
    Player &newPlayer(const TeamStrip in_strip);
    const sf::Texture &getMatchTexture();
    Camera &getCamera() {
        return *camera;
    }
    Team &getHomeTeam() {
        return *home_team;
    }
    Team &getAwayTeam() {
        return *away_team;
    }
    Ball &getBall() {
        return *ball;
    }
    Pitch &getPitch() {
        return *pitch;
    }
    MiniMap &getMinimap() {
        return *minimap;
    }
    void setAttackingTeam(const TeamStrip in_which);
    bool finished() {
        return false;
    }

    Player *player_in_possession = nullptr;

    std::unique_ptr<Team> home_team;
    std::unique_ptr<Team> away_team;
    std::unique_ptr<Ball> ball;
    std::unique_ptr<Pitch> pitch;
    std::unique_ptr<MiniMap> minimap;
    std::unique_ptr<Camera> camera;

protected:
    std::unique_ptr<sf::RenderTexture> match_texture;
    std::vector<std::unique_ptr<Player>> players;

    // debug checking for mem leakst
    static int instances;
};

}  // namespace Senseless
