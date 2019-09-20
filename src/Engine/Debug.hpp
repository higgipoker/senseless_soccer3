#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>

namespace Engine {
  /**
 * @brief The Debug class
 */
class Debug {
 public:
  /**
   * @brief Debug
   */
  Debug(sf::RenderWindow & in_window);
  /**
    */
  ~Debug();
  /**
   * @brief update
   */
  void update();
  /**
   * @brief pollEvent
   * @param in_event
   */
  void pollEvent(sf::Event &in_event);
  /// debug flags
  bool flag_draw_bounds= false;

private:
  /// target window
  sf::RenderWindow &window;
  /// a clock for ui tick
  sf::Clock ui_clock;
};

}  // namespace Engine
