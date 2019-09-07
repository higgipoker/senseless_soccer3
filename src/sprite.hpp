#pragma once
#include <SFML/Graphics/Sprite.hpp>

#include <string>
#include <vector>
// unused sprites have id -1
static const int NO_SPRITE = -1;
/**
 * @brief thin wrapper for sf::Sprite to make it sortable by z index,
 * and force informing the data pool when a z has changed (for sorting)
 */
struct SortableSprite : public sf::Sprite {
  static bool* sort_flag;
  float z = 0;
  std::string spritesheet;
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
/**
 * @brief populate_frames
 * @param frames
 * @param cols
 * @param width
 * @param height
 * @param frame_count
 */
void populate_frames(std::vector<sf::IntRect>& frames, int cols, int width,
                     int height, int start_row, int start_col, int frame_count);
