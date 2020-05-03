#pragma once
#include "Engine/BaseFactory.hpp"
#include "Engine/Types.hpp"
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
  static Team makeDefaultHomeTeam(const std::string& in_name);
  //
  //
  //
  static Team makeDefaultAwayTeam(const std::string& in_name);
  //
  //
  //
 private:
  static KitFactory kit_factory;
};
}  // namespace Senseless
