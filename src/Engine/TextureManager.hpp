#pragma once

#include <SFML/Graphics/Texture.hpp>

#include <cassert>
#include <iostream>
#include <map>

namespace Engine{
/**
 * @brief The CountedTexture struct
 */
struct CountedTexture {
  sf::Texture *texture;
  int count = 1;
};
/**
 * @brief The TextureManager class
 */
class TextureManager {
 public:
  /**
   * @brief acquireTexture
   * @param filename
   * @return
   */
  static sf::Texture *acquireTexture(const std::string &filename);

  /**
   * @brief releaseTexture
   * @param filename
   */
  static void releaseTexture(const std::string &filename);

  /**
   * @brief deleteTextures
   */
  void deleteTextures();

 private:
  /// track textures
  static std::map<std::string, CountedTexture> textures;
  /**
   * @brief make_counted_texture
   * @param tex
   * @return
   */
  static CountedTexture make_counted_texture(sf::Texture *tex);
};

}
