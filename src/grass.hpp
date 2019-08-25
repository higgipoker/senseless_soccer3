#pragma once
#include "entity.hpp"
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
  Entity::Entity *entity = nullptr;
  Entity::SortableSprite *sprite = nullptr;
  std::string spritesheet;
  int current_frame = 0;
};

// -----------------------------------------------------------------------------
// make_grass_sprite
// -----------------------------------------------------------------------------
inline void make_grass_sprite(Entity::SortableSprite *sprite,
                              const std::string &spritesheet) {
  sf::Texture *tex = Texture::acquire_texture(spritesheet);
  tex->setRepeated(true);
  sprite->sprite.setTexture(*tex);
  sprite->z_order = 0;
}

// -----------------------------------------------------------------------------
// init_grass
// -----------------------------------------------------------------------------
inline void init_grass(Grass &grass, const int x, const int y, const int w,
                       const int h) {
  Entity::Entity *e = Entity::acquire_entity();
  e->type = Entity::EntityType::Background;

  grass.entity = e;
  grass.spritesheet = grass_tile;
  grass.sprite = Entity::acquire_sprite();
  make_grass_sprite(grass.sprite, grass.spritesheet);
  grass.sprite->sprite.setTextureRect(sf::IntRect(x, y, w, h));
}

}  // namespace Grass
