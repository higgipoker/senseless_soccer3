#pragma once
#include "data.hpp"
#include "globals.hpp"
#include "texture.hpp"

#define GRASS_SPRITE(G) sprite_pool[entity_pool[grass.entity].sprite]
#define get_grass_entity(G) entity_pool[G.entity];

// types of grass
const std::array<std::string, 6> grasses{
    "grass_checked",    "grass_dry",   "grass_hard",
    "grass_horizontal", "grass_plain", "grass_plain_horizontal"};

// grass to use
inline std::string grass_tile{Globals::GFX_FOLDER + grasses.at(0) + ".png"};

/**
 * @brief The Grass struct
 */
struct Grass {
  int entity = 0;
  std::string spritesheet;
  int current_frame = 0;
};
/**
 * @brief make_grass_sprite
 * @param sprite
 * @param spritesheet
 */
void make_grass_sprite(int sprite, const std::string &spritesheet);
/**
 * @brief init_grass
 * @param grass
 * @param world_rect
 */
void init_grass(Grass &grass, Camera &camera);
/**
 * @brief update_grass
 * @param grass
 * @param window_rect
 */
void update_grass(Grass &grass, Camera &camera);
