#include "PlayerFactory.hpp"
//
#include "Match/Match.hpp"
#include "PlayerSprite.hpp"
#include "Team/KitFactory.hpp"
#include "Team/Team.hpp"
//
using namespace Engine;
//
//
//
std::unique_ptr<Player> PlayerFactory::makePlayer(Match &in_match, const Team &in_my_team, const Team &in_other_team, const TeamType in_strip) {
    auto shadow = std::make_unique<PlayerShadowSprite>(in_match.getMatchTexture());
    auto sprite = std::make_unique<PlayerSprite>(in_match.getMatchTexture(), in_strip);
    auto player = std::make_unique<Player>(in_match, in_my_team, in_other_team, std::move(sprite), std::move(shadow));
    return player;
}
