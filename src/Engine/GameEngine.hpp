#pragma once

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/View.hpp>
#include <map>
#include <vector>

#include "Camera.hpp"
#include "Controllable.hpp"
#include "Debug.hpp"
#include "Entity.hpp"
#include "Gamepad.hpp"
#include "Keyboard.hpp"
#include "Movable.hpp"
#include "Picker.hpp"
#include "Sprite.hpp"
#include "Window.hpp"

namespace Senseless {

using layer_id = size_t;

///
/// this allows for only sorting of layers which will change order
/// dynamically. For other layers just add drawable elements in
/// the correct order!
///
struct RenderLayer {
  RenderLayer(bool in_sortable = false, bool in_overlay = false)
      : sortable(in_sortable), overlay(in_overlay) {}
  bool sortable = false;
  bool overlay = false;
  std::vector<Sprite *> sprite_list;
  static const layer_id INVALID_LAYER = 999;
};

// ***************************************************************************
// *                                                                         *
// * GameEngine                                                              *
// *                                                                         *
// ***************************************************************************
class GameEngine {
 public:
  GameEngine(Camera &in_camera, const std::string &in_window_title = "Untitled",
             float in_window_width = 800, float in_window_height = 600,
             int in_flags = sf::Style::Default, bool in_fullscreen = false);
  ~GameEngine();
  void step() noexcept;
  int addLayer(const bool in_sortable = false,
               const bool in_overlay = false) noexcept;
  void addControllable(Controllable &in_controllable) noexcept;
  void addEntity(Entity &in_entity,
                 layer_id in_layer_id = RenderLayer::INVALID_LAYER) noexcept;
  bool isRunning() const noexcept;
  const sf::RenderTarget &getRenderTarget() const noexcept;
  Camera &getMainCamera() noexcept;
  layer_id getBackgroundLayer() const noexcept;
  layer_id getDefaultLayer() const noexcept;
  layer_id getShadowLayer() const noexcept;
  layer_id getHudLayer() const noexcept;
  const Keyboard &getDefaultKeyboard() const noexcept;
  Gamepad &getDefaultGamepad() noexcept;
  Debug &getDebugUI() noexcept { return debug_gui; }
  /// tmp
  int frame_counter = 0;

 private:
  Window window;
  Keyboard default_keyboard;
  Gamepad gamepad1;
  Camera &camera;
  Debug debug_gui;
  Picker picker;
  sf::View hud_view;
  std::vector<RenderLayer> render_layers;
  std::vector<Entity *> entities;
  std::vector<Controllable *> controllables;
  layer_id background_layer = RenderLayer::INVALID_LAYER;
  layer_id sprite_layer = RenderLayer::INVALID_LAYER;
  layer_id shadow_layer = RenderLayer::INVALID_LAYER;
  layer_id hud_layer = RenderLayer::INVALID_LAYER;
  sf::Clock clock;
  float dt = 0.01F;
  bool running = true;
  float last_time = 0;
  float frames = 0;
  float frametime = 0;
  //
  //
  //
  void add_sprite(Sprite &in_sprite,
                  layer_id in_layer_id = RenderLayer::INVALID_LAYER) noexcept;
  void toggle_debug(bool in_keep_on = false) noexcept;
  void poll_input_devices() noexcept;
};
}  // namespace Senseless
