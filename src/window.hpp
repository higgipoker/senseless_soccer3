#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/WindowStyle.hpp>

/**
 * @brief valid_videomode
 * @param width
 * @param height
 * @return
 */
bool valid_videomode(int width, int height);

/**
 * @brief init_window
 * @param window
 * @param title
 * @param width
 * @param height
 * @param flags
 * @param fullscreen
 */
void init_window(sf::RenderWindow &window, const std::string &title,
                 const int width, const int height, int flags,
                 bool fullscreen = false);

/**
 * @brief init_camera
 * @param view
 * @param width
 * @param height
 */
void init_camera(sf::View &view, const int width, const int height);
