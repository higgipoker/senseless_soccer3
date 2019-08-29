#pragma once
#include <SFML/Graphics/Sprite.hpp>

/**
 * @brief thin wrapper for sf::Sprite to make it sortable by z index,
 * and force informing the data pool when a z has changed (for sorting)
 */
struct SortableSprite : public sf::Sprite {
  /// for sorting
  static bool* sort_flag;
  float z = 0;
};

/**
 * @brief set_sprite_z
 * @param sprite
 * @param z
 */
void set_sprite_z(SortableSprite& sprite, float z);
