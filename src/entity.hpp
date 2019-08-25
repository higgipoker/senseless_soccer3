#pragma once

#include <gamelib3/math/vector.hpp>

#include <SFML/Graphics/Sprite.hpp>

#include <array>
#include <cassert>
#include <iostream>
#include <set>

namespace Entity {

/**
 * @brief The EntityType enum
 */
enum class EntityType { Anonymous, Match, Player, Ball, Background, Goal };

/**
 * @brief The Entity struct
 */
struct Entity {
  int id = -1;  // this is always the index of the array
  EntityType type = EntityType::Anonymous;
  gamelib3::Vector3 position, velocity, force;
  float co_friction = 0.01f;
  float mass = 1;
  sf::Sprite sprite;
};

inline const int MAX_SPRITES = 100;
inline const int MAX_ENTITIES = 100;

/**
 * @brief The SortableSprite struct
 */
struct SortableSprite {
  int z_order = 0;
  sf::Sprite sprite;
  bool live = false;
};

inline std::array<SortableSprite, MAX_SPRITES> sprites;
inline std::set<sf::Sprite*> used_sprites;

inline std::array<Entity, MAX_ENTITIES> entities;
inline std::array<bool, MAX_ENTITIES> used_entities;

inline std::array<Entity, 22> players;

inline int used_entity_count = 0;
inline int used_sprite_count = 0;

// -----------------------------------------------------------------------------
// acquire_entity
// -----------------------------------------------------------------------------
inline Entity* acquire_entity() {
  for (size_t i = 0; i < MAX_ENTITIES; ++i) {
    if (!used_entities[i]) {
      used_entities[i] = true;
      entities[i].id = i;
      ++used_entity_count;
      std::cout << "acquire_entity: used entities : " << used_entity_count
                << std::endl;
      return &entities[i];
    }
  }
  assert(false);
  return nullptr;
}

// -----------------------------------------------------------------------------
// release_entity
// -----------------------------------------------------------------------------
inline void release_entity(int id) {
  assert(id >= 0);
  assert(id < MAX_ENTITIES);
  assert(used_entities[id]);
  --used_entity_count;
  used_entities[id] = false;

  std::cout << "release_entity: used entities : " << used_entity_count
            << std::endl;
}

// -----------------------------------------------------------------------------
// acquire_sprite
// -----------------------------------------------------------------------------
inline SortableSprite* acquire_sprite() {
  for (auto& sprite : sprites) {
    if (used_sprites.find(&sprite.sprite) == used_sprites.end()) {
      sprite.live = true;
      used_sprites.insert(&sprite.sprite);
      ++used_sprite_count;
      std::cout << "acquire_sprite: used entities : " << used_sprite_count
                << std::endl;
      return &sprite;
    }
  }
  assert(false);
  return nullptr;
}

// -----------------------------------------------------------------------------
// release_sprite
// -----------------------------------------------------------------------------
inline void release_sprite(SortableSprite* sprite) {
  if (used_sprites.find(&sprite->sprite) != used_sprites.end()) {
    used_sprites.erase(&sprite->sprite);
    sprite->live = false;
    --used_sprite_count;
    std::cout << "release_sprite: used sprites : " << used_sprite_count
              << std::endl;
  } else {
    std::cout << "tried to release a non used sprite" << std::endl;
    assert(false);
  }
}

// -----------------------------------------------------------------------------
// think
// -----------------------------------------------------------------------------
inline void think(Entity& entity) {
  switch (entity.type) {
    default:
    case EntityType::Anonymous:
      break;
    case EntityType::Ball:
      break;
    case EntityType::Goal:
      break;
    case EntityType::Match:
      break;
    case EntityType::Player:
      break;
    case EntityType::Background:
      break;
  }
}
}  // namespace Entity
