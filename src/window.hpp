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
void init_window(sf::RenderWindow &window, const std::string &title, int width,
                 int height, int flags, bool fullscreen = false);
