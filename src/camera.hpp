#pragma once

#include "entity.hpp"
#include "game.hpp"

#include <SFML/Graphics/View.hpp>

/**
 * @brief The Camera struct
 */
struct Camera {
  Entity *entity = nullptr;
  sf::View view;
};
/**
 * @brief init_camera
 * @param camera
 * @param game
 */
void init_camera(Camera &camera, Game &game);
/**
 * @brief update_camera
 * @param camera
 * @param world_rect
 */
void update_camera(Camera &camera, sf::IntRect world_rect);
/**
 * @brief clamp_camera
 * @param camera
 * @param bounds
 */
void clamp_camera(Camera &camera, sf::IntRect bounds);
