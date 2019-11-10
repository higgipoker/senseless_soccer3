#include "TeamFactory.hpp"
//
#include "Team.hpp"
//
//
//
Team TeamFactory::makeDefaultHomeTeam() {
  auto kit = kit_factory.makeDefaultRedKit();
  return Team(TeamType::Home, kit);
}
//
//
//
Team TeamFactory::makeDefaultAwayTeam() {
  auto kit = kit_factory.makeDefaultBlueKit();
  return Team(TeamType::Away, kit);
}
