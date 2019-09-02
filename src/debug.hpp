#ifndef NDEBUG
#pragma once

#include "data.hpp"
#include "imgui/imgui-SFML.h"
#include "imgui/imgui.h"

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Clock.hpp>

#include <array>
#include <vector>

// unused entites have id -1
static const int NO_ENTITY = -1;

// turn on debug next frame
inline bool pending_debug_toggle = false;

// list of all bounds for debug
inline std::array<sf::IntRect, MAX_SPRITES> bounds;

// a clock for ui tick
inline sf::Clock ui_clock;

// currently grabbed entity id
inline int grabbed_entity = NO_ENTITY;

// where exactly the mouse was clicked
inline sf::Vector2f mousegrab_offset;

// list of shapes to render
inline std::vector<sf::Drawable *> debug_shapes;

// draw sprite bounds?
inline static bool bounds_flag = false;
/**
 * @brief init_debug
 * @param window
 */
void init_debug(sf::RenderWindow &window);
/**
 * @brief clean_debug
 */
void shutdown_debug();
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
/**
 * @brief grab_entity
 * @param id
 */
void grab_entity(int id, int mouse_x, int mouse_y);
/**
 * @brief release_entity
 */
void release_entity();
/**
 * @brief mouse_dragged
 */
void mouse_dragged(int x, int y);
#endif
