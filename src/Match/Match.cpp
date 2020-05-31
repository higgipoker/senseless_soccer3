#include "Match.hpp"
//
#include "Ball/BallSprite.hpp"
#include "Engine/EntityFactory.h"
#include "Game/Game.hpp"
#include "Team/Team.hpp"
//
#include <algorithm>
#include <cassert>

namespace Senseless {
//
int Match::instances = 0;
//
//
//
Match::Match(const Kit &in_home_kit, const Kit &in_away_kit)
    : Entity(std::make_unique<Sprite>(), std::make_unique<Sprite>()) {
  home_team = std::make_unique<Team>("Home Team");
  away_team = std::make_unique<Team>("Away Team");

  // texture for home team
  Texture home_texture;
  home_texture.loadFromFile(PlayerFactory::getSpriteSheeet(in_home_kit.type));
  home_texture.swapColors(in_home_kit.palette);

  // texture for away team
  Texture away_texture;
  away_texture.loadFromFile(PlayerFactory::getSpriteSheeet(in_away_kit.type));
  away_texture.swapColors(in_away_kit.palette);

  // shadow texture
  Texture shadow_texture;
  shadow_texture.loadFromFile(PlayerFactory::getShadowSheet());

  // ball texture
  BallFactory ball_factory;
  Texture ball_texture;
  ball_texture.loadFromFile(ball_factory.getSpriteSheeet(BallType::Standard));

  auto width = std::max(
      home_texture.getSize().x,
      std::max(away_texture.getSize().x,
               std::max(shadow_texture.getSize().x, ball_texture.getSize().x)));

  auto height = home_texture.getSize().y + away_texture.getSize().y +
                shadow_texture.getSize().y + ball_texture.getSize().y;

  match_texture = std::make_unique<sf::RenderTexture>();
  if (!match_texture->create(width, height)) {
    std::cout << "Could not create tecture with dimensions " << width << "x"
              << height << std::endl;
    std::cout << "Max texture dimensions: " << sf::Texture::getMaximumSize()
              << " x " << sf::Texture::getMaximumSize() << std::endl;
  }

  sf::Sprite s1(home_texture);
  sf::Sprite s2(away_texture);
  sf::Sprite s3(shadow_texture);
  sf::Sprite s4(ball_texture);
  s2.move(0, s1.getLocalBounds().height);
  s3.move(0, s2.getGlobalBounds().top + s2.getLocalBounds().height);
  s4.move(0, s3.getGlobalBounds().top + s3.getLocalBounds().height);

  match_texture->clear({0, 0, 0, 0});
  match_texture->draw(s1);
  match_texture->draw(s2);
  match_texture->draw(s3);
  match_texture->draw(s4);
  match_texture->display();

  ++instances;
  // std::cout << instances << " matches" << std::endl;
}
//
//
//
Match::~Match() {
  --instances;
  // std::cout << instances << " matches" << std::endl;
}
//
//
//
const sf::Texture &Match::getMatchTexture() {
  return match_texture->getTexture();
}
//
//
//
void Match::step() {}

//
//
//
void Match::setAttackingTeam(const TeamStrip in_which) {
  auto attacking_team = in_which;
  switch (attacking_team) {
    case TeamStrip::Home:
      gamestate->home_team->setAttackingState(AttackingState::Attacking);
      gamestate->away_team->setAttackingState(AttackingState::Defending);
      break;
    case TeamStrip::Away:
      gamestate->home_team->setAttackingState(AttackingState::Defending);
      gamestate->away_team->setAttackingState(AttackingState::Attacking);
      break;
  }
}
}  // namespace Senseless
