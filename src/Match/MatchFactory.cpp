#include "MatchFactory.hpp"
//
#include <SFML/Graphics/Sprite.hpp>
//
//
//
void MatchFactory::createMatchTexture(const Engine::Texture &team1_texture,
                                      const Engine::Texture &team2_texture,
                                      const Engine::Texture &shadow_texture,
                                      const Engine::Texture &ball_texture) {
  auto width = std::max(
      team1_texture.getSize().x,
      std::max(team2_texture.getSize().x,
               std::max(shadow_texture.getSize().x, ball_texture.getSize().x)));

  auto height = team1_texture.getSize().y + team2_texture.getSize().y +
                shadow_texture.getSize().y + ball_texture.getSize().y;

  sf::Sprite s1(team1_texture);
  sf::Sprite s2(team2_texture);
  sf::Sprite s3(shadow_texture);
  sf::Sprite s4(ball_texture);
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
}
//
//
//
const sf::Texture &MatchFactory::getMatchTexture() {
  return match_texture.getTexture();
}
