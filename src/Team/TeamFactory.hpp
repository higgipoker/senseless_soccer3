#pragma once
#include "Engine/BaseFactory.hpp"
#include <memory>
#include "Team/KitFactory.hpp"
namespace Senseless {
//
class Team;
//
//
//
class TeamFactory : public BaseFactory {
 public:
  //
  //
  //
  Team& makeDefaultHomeTeam(const std::string& in_name);
  //
  //
  //
  Team& makeDefaultAwayTeam(const std::string& in_name);
  //
  //
  //
  void reset();
 private:
  static KitFactory kit_factory;
  std::vector<std::unique_ptr<Team>> teams;
};
}  // namespace Senseless
