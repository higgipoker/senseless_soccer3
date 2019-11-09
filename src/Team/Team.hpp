#pragma once
#include "Player/Player.hpp"

#include "Player/PlayerFactory.hpp"
#include "Team/KitFactory.hpp"

#include "Engine/InputDevice.hpp"
#include "Engine/Texture.hpp"
#include "Engine/Types.hpp"

#include <SFML/Graphics/Texture.hpp>

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
    void update();
    //
    //
    //
    void addDefaultPlayers();
    //
    //
    //
    void addPlayer(UniquePtr<Player> in_player);
    //
    //
    //
    Player& getPlayer();
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
    UniquePtr<Engine::Texture> getSpriteTexture();
    //
    //
    //
    UniquePtr<Engine::Texture> getShadowTexture();

   protected:
    Match* match = nullptr;
    AttackingState attacking_state = AttackingState::Attacking;
    TeamType home_or_away = TeamType::Home;
    Kit kit;
    std::vector<UniquePtr<Player>> players;
    int loose_ball_ticks = 60;
    PlayerFactory player_factory;
    UniquePtr<Engine::Texture> sprite_texture = std::make_unique<Engine::Texture>();
    UniquePtr<Engine::Texture> shadow_texture = std::make_unique<Engine::Texture>();

   public:
    friend class Player;
};
