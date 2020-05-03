#pragma once
//
#include "Engine/BaseFactory.hpp"
#include "Engine/Texture.hpp"
#include "Engine/Types.hpp"
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
  bool createMatchTexture(UniquePtr<Texture> team1_texture, UniquePtr<Texture> team2_texture,
                          UniquePtr<Texture> shadow_texture1, UniquePtr<Texture> shadow_texture2,
                          UniquePtr<Texture> ball_texture);
  //
  //
  //
  const sf::Texture &getMatchTexture();

 private:
  sf::RenderTexture match_texture;
};
}  // namespace Senseless
