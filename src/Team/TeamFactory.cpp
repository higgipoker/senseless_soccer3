#include "TeamFactory.hpp"
//
//
//
UniquePtr<Team> TeamFactory::makeDefaultHomeTeam() {
  auto kit = kit_factory.makeDefaultRedKit();
  auto team = std::make_unique<Team>(TeamType::Home, kit);
  return team;
}
//
//
//
UniquePtr<Team> TeamFactory::makeDefaultAwayTeam() {
  auto kit = kit_factory.makeDefaultBlueKit();
  auto team = std::make_unique<Team>(TeamType::Away, kit);
  return team;
}
