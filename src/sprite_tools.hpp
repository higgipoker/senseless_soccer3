#pragma once

#include <SFML/Graphics/Sprite.hpp>
#include <vector>

/**
 * @brief populate_frames
 * @param frames
 * @param cols
 * @param width
 * @param height
 * @param frame_count
 */
void populate_frames(std::vector<sf::IntRect> &frames, int cols, int width,
                     int height, int start_row, int start_col, int frame_count);
