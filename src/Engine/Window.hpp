#pragma once

#include <SFML/Graphics/RenderWindow.hpp>

namespace Senseless{
class Window : public sf::RenderWindow {
 public:
  /**
   * @brief Window
   */
  Window(const std::string &title, const int width, const int height, int flags,
         bool fullscreen = false, const int in_fps=60);

 protected:
  /**
   * @brief validVideoMode
   * @param width
   * @param height
   * @return
   */
  static bool validVideoMode(unsigned int width, unsigned int height);
};
}
