#include "TextureManager.hpp"

namespace Engine {
std::map<std::string, CountedTexture> TextureManager::textures;
//
//
//
CountedTexture TextureManager::make_counted_texture(sf::Texture *tex) {
  CountedTexture ct;
  ct.texture = tex;
  return ct;
}
//
//
//
sf::Texture *TextureManager::acquireTexture(const std::string &filename) {
  sf::Texture *texture = nullptr;
  // only create new texture if doesnt exist already
  auto tex = textures.find(filename);
  if (tex != textures.end()) {
    texture = (*tex).second.texture;
    ++(*tex).second.count;
  } else {
    std::cout << "new texture" << std::endl;
    texture = new sf::Texture();
    texture->loadFromFile(filename);
    textures.insert(std::make_pair(filename, make_counted_texture(texture)));
  }
  return texture;
}
//
//
//
void TextureManager::releaseTexture(const std::string &filename) {
  auto it = textures.find(filename);
  if (it != textures.end()) {
    if (--(*it).second.count == 0) {
      std::cout << "delete texture" << std::endl;
      delete (*it).second.texture;
      textures.erase(it);
    }
  }
}
//
//
//
void TextureManager::deleteTextures() {
  for (auto &texture : textures) {
    delete texture.second.texture;
  }
}
}  // namespace Engine
