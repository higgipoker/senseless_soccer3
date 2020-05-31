#include "TeamFactory.hpp"
//
#include "Team.hpp"
namespace Senseless {
//
//
//
Team &TeamFactory::makeDefaultHomeTeam(const std::string &in_name) {
    auto kit = kit_factory.makeDefaultRedKit();
    auto team = std::make_unique<Team>(in_name);
    teams.push_back(std::move(team));
    return *teams.back();
}
//
//
//
Team &TeamFactory::makeDefaultAwayTeam(const std::string &in_name) {
    auto kit = kit_factory.makeDefaultBlueKit();
    auto team = std::make_unique<Team>(in_name);
    teams.push_back(std::move(team));
    return *teams.back();
}
//
//
//
void TeamFactory::reset(){
    teams.clear();
}
}  // namespace Senseless
