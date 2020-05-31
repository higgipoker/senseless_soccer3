#pragma once
//
#include "Engine/BaseFactory.hpp"
#include "Engine/Texture.hpp"
#include <memory>
//
#include <SFML/Graphics/RenderTexture.hpp>
namespace Senseless {
//
//
//
class MatchFactory : public BaseFactory {
 public:
  //
  //
  //
  bool createMatchTexture(std::unique_ptr<Texture> team1_texture, std::unique_ptr<Texture> team2_texture,
                          std::unique_ptr<Texture> shadow_texture1, std::unique_ptr<Texture> shadow_texture2,
                          std::unique_ptr<Texture> ball_texture);
  //
  //
  //
  const sf::Texture &getMatchTexture();

 private:
  sf::RenderTexture match_texture;
};
}  // namespace Senseless
