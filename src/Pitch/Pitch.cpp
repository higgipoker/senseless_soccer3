#include "Pitch.hpp"

#include "Engine/TextureManager.hpp"

#include <SFML/Graphics/Texture.hpp>
//
//
//
Pitch::Pitch(const std::string& in_filename) {
  sf::Texture* tex = Engine::TextureManager::acquireTexture(in_filename);
  tex->setRepeated(true);
  setTexture(*tex);
}
//
//
//
void Pitch::setRect(const sf::IntRect in_rect){
  camera_rect = in_rect;
  setTextureRect(camera_rect);
}
