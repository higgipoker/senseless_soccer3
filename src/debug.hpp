#pragma once

#include "data.hpp"
#include "imgui/imgui-SFML.h"
#include "imgui/imgui.h"

#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Clock.hpp>

#include <array>
inline bool pending_debug_toggle = false;
inline std::array<sf::IntRect, MAX_SPRITES> bounds;
inline sf::Clock ui_clock;
/**
 * @brief init_debug
 * @param window
 */
void init_debug(sf::RenderWindow &window);
/**
 * @brief clean_debug
 */
void clean_debug();
/**
 * @brief update_debug
 * @param window
 */
void update_debug(sf::RenderWindow &window);
/**
 * @brief draw_bounds
 * @param window
 * @param bounds
 */
void draw_bounds(sf::RenderWindow &window, sf::FloatRect bounds);
/**
 * @brief render_debug
 * @param window
 */
void render_debug(sf::RenderWindow &window);
/**
 * @brief toggle_debug
 */
void toggle_debug();
