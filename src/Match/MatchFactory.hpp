#pragma once
//
#include "Engine/BaseFactory.hpp"
#include "Engine/Texture.hpp"
#include "Engine/Types.hpp"
//
#include <SFML/Graphics/RenderTexture.hpp>
//
//
//
class MatchFactory : public Engine::BaseFactory {
 public:
  //
  //
  //
  void createMatchTexture(UniquePtr<Engine::Texture> team1_texture,
                          UniquePtr<Engine::Texture> team2_texture,
                          UniquePtr<Engine::Texture> shadow_texture1,
                          UniquePtr<Engine::Texture> shadow_texture2,
                          UniquePtr<Engine::Texture> ball_texture);
  //
  //
  //
  const sf::Texture &getMatchTexture();

 private:
  sf::RenderTexture match_texture;
};
