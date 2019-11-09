#include "MatchFactory.hpp"
//
#include <SFML/Graphics/Sprite.hpp>
//
//
//
void MatchFactory::createMatchTexture(UniquePtr<Engine::Texture> team1_texture,
                                      UniquePtr<Engine::Texture> team2_texture,
                                      UniquePtr<Engine::Texture> shadow_texture,
                                      UniquePtr<Engine::Texture> ball_texture) {
  auto width = std::max(
      team1_texture->getSize().x,
      std::max(team2_texture->getSize().x,
               std::max(shadow_texture->getSize().x, ball_texture->getSize().x)));

  auto height = team1_texture->getSize().y + team2_texture->getSize().y +
                shadow_texture->getSize().y + ball_texture->getSize().y;

  sf::Sprite s1(*team1_texture.get());
  sf::Sprite s2(*team2_texture.get());
  sf::Sprite s3(*shadow_texture.get());
  sf::Sprite s4(*ball_texture.get());
  s2.move(0, s1.getLocalBounds().height);
  s3.move(0, s2.getGlobalBounds().top + s2.getLocalBounds().height);
  s4.move(0, s3.getGlobalBounds().top + s3.getLocalBounds().height);

  match_texture.create(width, height);
  match_texture.clear({0, 0, 0, 0});
  match_texture.draw(s1);
  match_texture.draw(s2);
  match_texture.draw(s3);
  match_texture.draw(s4);
  match_texture.display();

  team1_texture.release();
  team2_texture.release();
}
//
//
//
const sf::Texture &MatchFactory::getMatchTexture() {
  return match_texture.getTexture();
}
