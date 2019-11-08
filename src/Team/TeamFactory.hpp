#pragma once
#include "Engine/BaseFactory.hpp"
#include "Engine/Types.hpp"
#include "Player/PlayerFactory.hpp"
#include "Team/KitFactory.hpp"
#include "Team/Team.hpp"
//
//
//
class TeamFactory : public Engine::BaseFactory {
 public:
  //
  //
  //
  UniquePtr<Team> makeDefaultHomeTeam();
  //
  //
  //
  UniquePtr<Team> makeDefaultAwayTeam();
  //
  //
  //
 private:
  KitFactory kit_factory;
  PlayerFactory player_factory;
};
