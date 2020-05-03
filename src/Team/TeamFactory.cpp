#include "TeamFactory.hpp"
//
#include "Team.hpp"
namespace Senseless {
//
//
//
Team TeamFactory::makeDefaultHomeTeam(const std::string &in_name) {
  auto kit = kit_factory.makeDefaultRedKit();
  return Team(in_name, TeamType::Home, kit);
}
//
//
//
Team TeamFactory::makeDefaultAwayTeam(const std::string &in_name) {
  auto kit = kit_factory.makeDefaultBlueKit();
  return Team(in_name, TeamType::Away, kit);
}

}  // namespace Senseless
