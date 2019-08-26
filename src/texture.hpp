#pragma once

#include <SFML/Graphics/Texture.hpp>

#include <cassert>
#include <iostream>
#include <map>

namespace Texture {

/**
 * @brief The CountedTexture struct
 */
struct CountedTexture {
  CountedTexture(sf::Texture *tex) : texture(tex) {}
  sf::Texture *texture;
  int count = 1;
};

inline std::map<std::string, CountedTexture> textures;

// -----------------------------------------------------------------------------
// acquire_texture
// -----------------------------------------------------------------------------
inline sf::Texture *acquire_texture(const std::string &filename) {
  sf::Texture *texture = nullptr;
  // only create new texture if doesnt exist already
  auto tex = textures.find(filename);
  if (tex != textures.end()) {
    texture = (*tex).second.texture;
    ++(*tex).second.count;
  } else {
    texture = new sf::Texture();
    texture->loadFromFile(filename);
    textures.insert(std::make_pair(filename, CountedTexture(texture)));
    std::cout << "load texture from " << filename << std::endl;
  }
  assert(texture);
  return texture;
}

// -----------------------------------------------------------------------------
// release_texture
// -----------------------------------------------------------------------------
inline void release_texture(const std::string &filename) {
  auto it = textures.find(filename);
  if (it != textures.end()) {
    if (--(*it).second.count == 0) {
      delete (*it).second.texture;
      textures.erase(it);
      std::cout << "released texture " << filename << ", no refs remain!"
                << std::endl;
    } else {
      std::cout << "released texture " << filename << " but "
                << (*it).second.count << " refs still exist" << std::endl;
    }
  }
}

// -----------------------------------------------------------------------------
// cleanup
// -----------------------------------------------------------------------------
inline void cleanup() {
  for (auto &texture : textures) {
    delete texture.second.texture;
  }
}

}  // namespace Texture
