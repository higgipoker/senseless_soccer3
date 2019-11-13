#pragma once
#include "Gameplan.hpp"
#include "KitFactory.hpp"
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
    //
    //
    //
    Team(const TeamType in_home_or_away, const Kit& in_kit);
    //
    //
    //
    ~Team();
    //
    //
    //
    void setAttackingGoal(Engine::Direction in_dir);
    //
    //
    //
    void update();
    //
    //
    //
    void addDefaultPlayers(const Team & in_other_team);
    //
    //
    //
    void addPlayer(UniquePtr<Player> in_player);
    //
    //
    //
    inline bool hasPlayers() {
        return !players.empty();
    }
    //
    //
    //
    Player& getPlayer(const size_t in_which);
    //
    //
    //
    size_t numberPlayers() {
        return players.size();
    }
    //
    //
    //
    TeamType getTeamType() {
        return home_or_away;
    }
    //
    //
    //
    void setMatch(Match& in_match);
    //
    //
    //
    Engine::Direction getAttackingGoal() const;
    //
    //
    //
    Engine::Direction getDefendingGoal() const;
    //
    //
    //
    UniquePtr<Engine::Texture> getSpriteTexture();
    //
    //
    //
    UniquePtr<Engine::Texture> getShadowTexture();
    //
    //
    //
    Gameplan gameplan;
    // a team has its own sprite for rendering debug primitives etc
    Engine::Sprite sprite;

   protected:
    Match* match = nullptr;
    AttackingState attacking_state = AttackingState::Attacking;
    TeamType home_or_away = TeamType::Home;
    Kit kit;
    std::vector<UniquePtr<Player>> players;
    int loose_ball_ticks = 60;
    Engine::Vector3 last_ball_position;
    PlayerFactory player_factory;
    Engine::Direction attacking_goal = Engine::Direction::South;
    Engine::Direction defending_goal = Engine::Direction::North;
    UniquePtr<Engine::Texture> sprite_texture = std::make_unique<Engine::Texture>();
    UniquePtr<Engine::Texture> shadow_texture = std::make_unique<Engine::Texture>();

    // debugs
    sf::RectangleShape defensive_line;

    static int instances;

   public:
    friend class Player;
};
