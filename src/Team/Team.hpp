#pragma once
#include "Player/Player.hpp"

#include <memory>
#include <vector>
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
  void addPlayer(UniquePtr<Player> in_player);
  //
  //
  //
  Player& getPlayer();
  //
  //
  //
  inline bool hasPlayers(){return !players.empty();}

private:
  std::vector<UniquePtr<Player>> players;
};
