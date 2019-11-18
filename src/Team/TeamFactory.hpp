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
  Team makeDefaultHomeTeam(const std::string & in_name);
  //
  //
  //
  Team makeDefaultAwayTeam(const std::string & in_name);
  //
  //
  //
 private:
  KitFactory kit_factory;
};
