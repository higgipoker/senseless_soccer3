#pragma once
#include "Player/Player.hpp"

#include <memory>
#include <vector>
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
  Team();
  //
  //
  //
  void update();
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
  struct {
    void clear() {
      short_pass_candidates.clear();
      long_pass_candidates.clear();
      pressuring_players.clear();
      press_list.clear();
      closest_to_ball = nullptr;
    }
    std::vector<Player*> short_pass_candidates;
    std::vector<Player*> long_pass_candidates;
    std::vector<Player*> pressuring_players;
    std::vector<Player*> press_list;
    Player* closest_to_ball = nullptr;
  } key_players;
  //
  //
  //
  static Match* match;

 protected:
  std::vector<UniquePtr<Player>> players;
  //
  //
  //
  void set_key_players();

public:
  friend class Player;
};
