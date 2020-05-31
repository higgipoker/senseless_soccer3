#include "MatchFactory.hpp"
//
#include <SFML/Graphics/Sprite.hpp>
namespace Senseless {
//
//
//
const sf::Texture& MatchFactory::newMatchTexture(std::unique_ptr<Texture> team1_texture,
                                      std::unique_ptr<Texture> team2_texture,
                                      std::unique_ptr<Texture> shadow_texture1,
                                      std::unique_ptr<Texture> shadow_texture2,
                                      std::unique_ptr<Texture> ball_texture) {
  auto width = std::max(team1_texture->getSize().x,
                        std::max(team2_texture->getSize().x, std::max(shadow_texture1->getSize().x,
                                                                      ball_texture->getSize().x)));

  auto height = team1_texture->getSize().y + team2_texture->getSize().y +
                shadow_texture1->getSize().y + ball_texture->getSize().y;

  if (!match_texture->create(width, height)) {
    std::cout << "Could not create tecture with dimensions " << width << "x" << height << std::endl;
    std::cout << "Max texture dimensions: " << sf::Texture::getMaximumSize() << " x "
              << sf::Texture::getMaximumSize() << std::endl;    
  }

  sf::Sprite s1(*team1_texture);
  sf::Sprite s2(*team2_texture);
  sf::Sprite s3(*shadow_texture1);
  sf::Sprite s4(*ball_texture.get());
  s2.move(0, s1.getLocalBounds().height);
  s3.move(0, s2.getGlobalBounds().top + s2.getLocalBounds().height);
  s4.move(0, s3.getGlobalBounds().top + s3.getLocalBounds().height);

  match_texture->clear({0, 0, 0, 0});
  match_texture->draw(s1);
  match_texture->draw(s2);
  match_texture->draw(s3);
  match_texture->draw(s4);
  match_texture->display();

  // once the textures have been copied to the match texture, we can get rid of them out of memory
  team1_texture.reset();
  team2_texture.reset();
  shadow_texture1.reset();
  shadow_texture2.reset();
  return match_texture->getTexture();
}

}  // namespace Senseless
