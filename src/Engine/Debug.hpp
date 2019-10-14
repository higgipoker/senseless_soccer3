#pragma once
#ifndef NDEBUG
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
  Debug(sf::RenderWindow &in_window);
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
  //
  //
  //
  static void toggle();
  //
  //
  //
  static bool showHud();
  //
  //
  //
  static bool drawBounds();
  //
  //
  //
  static bool drawDiagnostics();
  //
  //
  //
  static sf::Color defaultBoundsColor();
  //
  //
  //
  static sf::Color defaultDiagnosticsColor();

 private:
  /// target window
  sf::RenderWindow &window;
  /// a clock for ui tick
  sf::Clock ui_clock;

  /// debug flags
  static bool flag_draw_bounds;
  static sf::Color bounds_color;
  static bool flag_draw_diagnostics;
  static sf::Color disgnostics_color;

  /// display debug gui?
  static bool show_debug_hud;
};

}  // namespace Engine
#endif
