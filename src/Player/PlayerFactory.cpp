#include "PlayerFactory.hpp"
//
#include "PlayerSprite.hpp"
//
#include "Team/Team.hpp"
//
using namespace Engine;
//
//
//
std::unique_ptr<Player> PlayerFactory::makePlayer(
    const sf::Texture &in_spritesheet, const TeamType in_strip) {
  auto shadow = std::make_unique<PlayerShadowSprite>(in_spritesheet);
  auto sprite = std::make_unique<PlayerSprite>(in_spritesheet, in_strip);
  auto player = std::make_unique<Player>(std::move(sprite), std::move(shadow));
  return player;
}
