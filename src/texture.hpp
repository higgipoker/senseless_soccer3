#pragma once

#include <SFML/Graphics/Texture.hpp>

#include <cassert>
#include <iostream>
#include <map>
/**
 * @brief The CountedTexture struct
 */
struct CountedTexture {
  sf::Texture *texture;
  int count = 1;
};
static std::map<std::string, CountedTexture> textures;
/**
 * @brief make_counted_texture
 * @param tex
 * @return
 */
CountedTexture make_counted_texture(sf::Texture *tex);
/**
 * @brief acquire_texture
 * @param filename
 * @return
 */
sf::Texture *acquire_texture(const std::string &filename);
/**
 * @brief release_texture
 * @param filename
 */
void release_texture(const std::string &filename);
/**
 * @brief cleanup
 */
void delete_textures();
