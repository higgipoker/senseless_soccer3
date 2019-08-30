#include "data.hpp"
#include <stack>

enum class SortAlgorithm { Bubble, Selection };
bool* SortableSprite::sort_flag = &sprite_pool_sorted;

// -----------------------------------------------------------------------------
// acquire_entity
// -----------------------------------------------------------------------------
int acquire_entity() {
  if (used_entity_count == MAX_ENTITIES) {
    std::cout << "ran out of entities. Max: " << MAX_ENTITIES << std::endl;
    return -1;
  }
  for (size_t i = 0; i < MAX_ENTITIES; ++i) {
    if (!used_entities[i]) {
      used_entities[i] = true;
      ++used_entity_count;
      entity_pool[i].id = i;
      return i;
    }
  }
  std::cout << "failed to acquire an entity" << std::endl;
  assert(false);
  return -1;
}

// -----------------------------------------------------------------------------
// release_entity
// -----------------------------------------------------------------------------
void release_entity(int id) {
  assert(id >= 0);
  assert(id < MAX_ENTITIES);
  assert(used_entities[id]);
  entity_pool[id].id = -1;
  --used_entity_count;
  used_entities[id] = false;
}

// -----------------------------------------------------------------------------
// acquire_sprite
// -----------------------------------------------------------------------------
int acquire_sprite(Entity* e) {
  if (used_sprite_count == MAX_SPRITES) {
    std::cout << "ran out of sprites. Max: " << MAX_SPRITES << std::endl;
    return -1;
  }
  for (size_t i = 0; i < MAX_SPRITES; ++i) {
    SortableSprite* addr = &sprite_pool[i];
    if (used_sprites.find(addr) == used_sprites.end()) {
      if (used_sprites.insert(std::make_pair(addr, i)).second == false) {
        std::cout << "insertion failed" << std::endl;
      }
      ++used_sprite_count;
      if (e) {
        sprite_callbacks.insert(std::make_pair(e, i));
      }
      sprite_pool_dirty = true;
      pack_sprite_pool();
      return i;
    }
  }
  std::cout << "failed to acquire sprite!" << std::endl;
  assert(false);
  return -1;
}

// -----------------------------------------------------------------------------
// release_sprite
// -----------------------------------------------------------------------------
void release_sprite(int id) {
  auto sprite = &sprite_pool[id];
  if (used_sprites.find(sprite) != used_sprites.end()) {
    used_sprites.erase(sprite);
    --used_sprite_count;
    sprite_pool_dirty = true;
    if (auto entity = find_sprite_callback(id)) {
      sprite_callbacks.erase(sprite_callbacks.find(entity));
    }
  }
  pack_sprite_pool();
}

// -----------------------------------------------------------------------------
// find_sprite_callback
// -----------------------------------------------------------------------------
Entity* find_sprite_callback(int i) {
  Entity* ret = nullptr;
  for (auto& callback : sprite_callbacks) {
    if (callback.second == i) {
      return callback.first;
    }
  }
  return ret;
}

// -----------------------------------------------------------------------------
// swap_sprites
// -----------------------------------------------------------------------------
void swap_sprites(const int idx1, const int idx2) {
  if (idx1 == idx2) return;
  SortableSprite tmp = sprite_pool[idx1];
  sprite_pool[idx1] = sprite_pool[idx2];
  sprite_pool[idx2] = tmp;

  // update used sprites with new indexes
  used_sprites.erase(&sprite_pool[idx1]);
  used_sprites.erase(&sprite_pool[idx2]);
  used_sprites.insert(std::make_pair(&sprite_pool[idx1], idx1));
  used_sprites.insert(std::make_pair(&sprite_pool[idx2], idx2));

  auto entity1 = find_sprite_callback(idx1);
  auto entity2 = find_sprite_callback(idx2);

  // update the callbacks
  if (entity1) {
    // update the entity with the new index!
    entity1->sprite = idx2;
    sprite_callbacks.erase(sprite_callbacks.find(entity1));
    sprite_callbacks.insert(std::make_pair(entity1, idx2));
  }
  if (entity2) {
    // update the entity with the new index!
    entity2->sprite = idx1;
    sprite_callbacks.erase(sprite_callbacks.find(entity2));
    sprite_callbacks.insert(std::make_pair(entity2, idx1));
  }
}
// -----------------------------------------------------------------------------
// places all used sprites at the top of the list
// -----------------------------------------------------------------------------
void pack_sprite_pool() {
  if (used_sprites.empty()) return;

  int swaps = 0;
  std::stack<int> free_slots;
  for (size_t i = 0; i < MAX_SPRITES - 1; ++i) {
    // this is not used
    if (used_sprites.find(&sprite_pool[i]) == used_sprites.end()) {
      free_slots.push(i);
    } else {
      if (!free_slots.empty()) {
        swaps++;
        swap_sprites(free_slots.top(), i);
        free_slots.pop();
      }
    }
  }
}

// -----------------------------------------------------------------------------
// sorts the sprite pool based on z order (MUST BE PACKED FIRST!)
// -----------------------------------------------------------------------------
void sort_sprite_pool() {
  if (used_sprites.size() < 2) return;

  // simple selection sort is fine because array is quite small
  static const int MAX_Z = 1000;
  int head = 0;
  while (head < used_sprite_count) {
    int min_z = MAX_Z;
    int min_idx = 0;
    for (int i = head; i < used_sprite_count; ++i) {
      if (sprite_pool[i].z < min_z) {
        min_z = sprite_pool[i].z;
        min_idx = i;
      }
    }
    // swap the min with the head
    if (min_idx != head) {  // the first iteration these could be equal
      swap_sprites(head, min_idx);
    }
    head++;
  }
  sprite_pool_sorted = true;
}
