#pragma once
#include "Engine/BaseFactory.hpp"
#include "Engine/Types.hpp"
#include "Team/KitFactory.hpp"
//
class Team;
//
//
//
class TeamFactory : public Engine::BaseFactory {
 public:
  //
  //
  //
  Team makeDefaultHomeTeam();
  //
  //
  //
  Team makeDefaultAwayTeam();
  //
  //
  //
 private:
  KitFactory kit_factory;
};
