#pragma once
#include "data.hpp"
#include "globals.hpp"
#include "texture.hpp"
namespace Grass {

inline const std::array<std::string, 6> grasses{
    "grass_checked",    "grass_dry",   "grass_hard",
    "grass_horizontal", "grass_plain", "grass_plain_horizontal"};

const std::string grass_tile{Globals::GFX_FOLDER + grasses.at(0) + ".png"};

/**
 * @brief The Grass struct
 */
struct Grass {
  int entity = 0;
  std::string spritesheet;
  int current_frame = 0;
};

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
inline sf::Sprite &get_sprite(Grass &grass) {
  return Data::sprite_pool[Data::entity_pool[grass.entity].sprite];
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
inline Data::Entity &get_entity(Grass &grass) {
  return Data::entity_pool[grass.entity];
}

// -----------------------------------------------------------------------------
// make_grass_sprite
// -----------------------------------------------------------------------------
inline void make_grass_sprite(int sprite, const std::string &spritesheet) {
  sf::Texture *tex = Texture::acquire_texture(spritesheet);
  tex->setRepeated(true);
  Data::sprite_pool[sprite].setTexture(*tex);
  Data::sprite_pool[sprite].set_z(0);
}

// -----------------------------------------------------------------------------
// init_grass
// -----------------------------------------------------------------------------
inline void init_grass(Grass &grass, const int x, const int y, const int w,
                       const int h) {
  int e = Data::acquire_entity();
  Data::entity_pool[e].type = Data::EntityType::Background;

  grass.entity = e;
  grass.spritesheet = grass_tile;
  Data::entity_pool[e].sprite = Data::acquire_sprite(&Data::entity_pool[e]);
  make_grass_sprite(Data::entity_pool[e].sprite, grass.spritesheet);
  get_sprite(grass).setTextureRect(sf::IntRect(x, y, w, h));
}

}  // namespace Grass
