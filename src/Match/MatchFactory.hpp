#pragma once
//
#include <Engine/BaseFactory.hpp>
#include <Engine/Texture.hpp>
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
  void createMatchTexture(const Engine::Texture &team1_texture,
                          const Engine::Texture &team2_texture,
                          const Engine::Texture &shadow_texture,
                          const Engine::Texture &ball_texture);
  //
  //
  //
  const sf::Texture &getMatchTexture();

 private:
  sf::RenderTexture match_texture;
};
