#include "texture.hpp"

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
CountedTexture make_counted_texture(sf::Texture *tex) {
  CountedTexture ct;
  ct.texture = tex;
  return ct;
}

// -----------------------------------------------------------------------------
// acquire_texture
// -----------------------------------------------------------------------------
sf::Texture *acquire_texture(const std::string &filename) {
  sf::Texture *texture = nullptr;
  // only create new texture if doesnt exist already
  auto tex = textures.find(filename);
  if (tex != textures.end()) {
    texture = (*tex).second.texture;
    ++(*tex).second.count;
  } else {
    texture = new sf::Texture();
    texture->loadFromFile(filename);
    textures.insert(std::make_pair(filename, make_counted_texture(texture)));
  }
  assert(texture);
  return texture;
}

// -----------------------------------------------------------------------------
// release_texture
// -----------------------------------------------------------------------------
void release_texture(const std::string &filename) {
  auto it = textures.find(filename);
  if (it != textures.end()) {
    if (--(*it).second.count == 0) {
      delete (*it).second.texture;
      textures.erase(it);
    }
  }
}

// -----------------------------------------------------------------------------
// cleanup
// -----------------------------------------------------------------------------
void cleanup() {
  for (auto &texture : textures) {
    delete texture.second.texture;
  }
}
