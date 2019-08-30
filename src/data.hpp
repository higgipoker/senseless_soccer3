#pragma once

#include "entity.hpp"
#include "input.hpp"
#include "sprite.hpp"

#include <gamelib3/math/vector.hpp>

#include <array>
#include <cassert>
#include <iostream>
#include <map>

// -----------------------------------------------------------------------------
//
// THE DATA!
//
// -----------------------------------------------------------------------------
inline const int MAX_SPRITES = 50;
inline const int MAX_ENTITIES = 50;
inline Entity entity_pool[MAX_ENTITIES];
inline SortableSprite sprite_pool[MAX_SPRITES];

// -----------------------------------------------------------------------------
//
// data management and tracking
//
// -----------------------------------------------------------------------------
inline std::map<Entity*, int> entity_callbacks;      // track changes
inline std::map<Entity*, int> sprite_callbacks;      // track changes
inline bool used_entities[MAX_ENTITIES];             // tracks used slots
inline std::map<SortableSprite*, int> used_sprites;  // tracks used slots
inline int used_entity_count = 0;  // convenience counter, synced with above
inline int used_sprite_count = 0;  // convenience counter, synced with above
inline bool sprite_pool_dirty = false;  // need to pack the pool
inline bool sprite_pool_sorted = true;  // need to sort the pool

/**
 * @brief find_sprite_callback
 * @param i
 * @return
 */
Entity* find_sprite_callback(int i);
/**
 * @brief swaps 2 sprites (eg for sorting algorithm)
 * @param idx1
 * @param idx2
 */
void swap_sprites(const int idx1, const int idx2);
/**
 * @brief moves all sprites to the top of the list
 */
void pack_sprite_pool();
/**
 * @brief sorts sprite pool in render order
 */
void sort_sprite_pool();
/**
 * @brief reserves an entity from the pool
 * @return
 */
int acquire_entity();
/**
 * @brief release_entity
 * @param id
 */
void release_entity(int id);
/**
 * @brief acquire_sprite
 * @param e
 * @return
 */
int acquire_sprite(Entity* e = nullptr);
/**
 * @brief release_sprite
 * @param id
 */
void release_sprite(int id);
/**
 * @brief entities_available
 * @return
 */
int entities_available();
/**
 * @brief sprites_available
 * @return
 */
int sprites_available();
/**
 * @brief get_sprite
 * @param e
 * @return
 */
inline sf::Sprite* get_sprite(Entity& e) { return &sprite_pool[e.sprite]; }
