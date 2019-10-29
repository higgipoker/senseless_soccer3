#include "Team.hpp"

//
//
//
Team::Team() {}
//
//
//
void Team::addPlayer(UniquePtr<Player> in_player){
  players.push_back(std::move(in_player));
}
//
//
//
Player& Team::getPlayer(){
  return *players.back();
}
