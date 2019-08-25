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
  sf::Sprite sprite;
};

static const int MAX_SPRITES = 100;
static const int MAX_ENTITIES = 100;

/**
 * @brief The SortableSprite struct
 */
struct SortableSprite {
  int z_order = 0;
  sf::Sprite sprite;
};

static std::array<SortableSprite, MAX_SPRITES> sprites;
static std::set<sf::Sprite*> used_sprites;

static std::array<Entity, MAX_ENTITIES> entities;
static std::array<bool, MAX_ENTITIES> used_entities;

static std::array<Entity, 22> players;

static int used_entity_count = 0;
static int used_sprite_count = 0;

// -----------------------------------------------------------------------------
// sort_sprites
// -----------------------------------------------------------------------------
inline bool sprite_sort_predicate(const SortableSprite& s1,
                                  const SortableSprite& s2) {
  return s1.z_order < s2.z_order;
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
static void sort_sprites() {
  std::sort(sprites.begin(), sprites.end(), sprite_sort_predicate);
}
// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
static Entity* acquire_entity() {
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
//
// -----------------------------------------------------------------------------
static void release_entity(int id) {
  assert(id >= 0);
  assert(id < MAX_ENTITIES);
  assert(used_entities[id]);
  --used_entity_count;
  used_entities[id] = false;

  std::cout << "release_entity: used entities : " << used_entity_count
            << std::endl;
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
static SortableSprite* acquire_sprite() {
  for (auto& sprite : sprites) {
    if (used_sprites.find(&sprite.sprite) == used_sprites.end()) {
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
//
// -----------------------------------------------------------------------------
static void release_sprite(SortableSprite* sprite) {
  if (used_sprites.find(&sprite->sprite) != used_sprites.end()) {
    used_sprites.erase(&sprite->sprite);
    --used_sprite_count;
    std::cout << "release_sprite: used sprites : " << used_sprite_count
              << std::endl;
  } else {
    std::cout << "tried to release a non used sprite" << std::endl;
    assert(false);
  }
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
static void think(Entity& entity) {
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
