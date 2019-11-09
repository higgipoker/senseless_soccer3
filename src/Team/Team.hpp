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
  ~Team() { std::cout << "Destruct Team" << std::endl; }
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
  inline bool hasPlayers() { return !players.empty(); }
  //
  //
  //
  void attachInputDevice(Engine::InputDevice& in_device);
  //
  //
  //
  struct {
    void clear() {
      short_pass_candidates.clear();
      long_pass_candidates.clear();
      pressuring_players.clear();
      press_list.clear();
      closest_to_ball = nullptr;
      last_in_possession = nullptr;
    }
    std::vector<Player*> short_pass_candidates;
    std::vector<Player*> long_pass_candidates;
    std::vector<Player*> pressuring_players;
    std::vector<Player*> press_list;
    Player* closest_to_ball = nullptr;
    Player* last_in_possession = nullptr;
    Player* last_retriever = nullptr;
    Player* pass_receiver = nullptr;
  } key_players;
  //
  //
  //
  static Match* match;
  //
  //
  //
  Player& getPlayer(const size_t in_which);
  //
  //
  //
  size_t numberPlayers() { return players.size(); }
  //
  //
  //
  TeamType getTeamType() { return home_or_away; }

 protected:
  UniquePtr<Engine::Texture> sprite_texture =
      std::make_unique<Engine::Texture>();
  UniquePtr<Engine::Texture> shadow_texture =
      std::make_unique<Engine::Texture>();
  PlayerFactory player_factory;
  std::vector<UniquePtr<Player>> players;

  void set_key_players();
  int loose_ball_ticks = 60;
  Engine::InputDevice* input = nullptr;
  TeamType home_or_away;
  Kit kit;

 public:
  friend class Player;
};
