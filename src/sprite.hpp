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
/**
 * @brief perspectivize
 * @param sprite
 * @param z
 * @param width
 * @param camera_height
 */
bool perspectivize(sf::Sprite& sprite, float z, float width,
                   float camera_height);
/**
 * @brief get_sprite
 * @param entity
 * @return
 */
sf::Sprite& get_sprite(int entity);
