#pragma once

#include "Camera.hpp"
#include "Debug.hpp"
#include "Entity.hpp"
#include "Gamepad.hpp"
#include "Keyboard.hpp"
#include "Movable.hpp"
#include "Sprite.hpp"
#include "Window.hpp"

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/View.hpp>

#include <map>
#include <vector>

namespace Engine {

using layer_id = size_t;

///
/// this allows for only sorting of layers which will change order
/// dynamically. For other layers just add drawable elements in
/// the correct order!
///
struct RenderLayer {
  RenderLayer(bool in_sortable = false) : sortable(in_sortable) {}
  std::vector<Sprite *> sprite_list;
  bool sortable = false;
  static const layer_id INVALID_LAYER = 999;
};

/**
 * @brief The Engine class
 */
class GameEngine {
 public:
  //
  //
  //
  GameEngine(const std::string &in_window_title = "Untitled",
             int in_window_width = 800, int in_window_height = 600,
             int in_flags = sf::Style::Default, bool in_fullscreen = false);
  //
  //
  //
  ~GameEngine();
  //
  //
  //
  void step();
  //
  //
  //
  int addLayer(bool in_sortable = false);
  //
  //
  //
  void addSprite(Sprite &in_sprite,
                 layer_id in_layer_id = RenderLayer::INVALID_LAYER);
  //
  //
  //
  void addEntity(Entity &in_entity,
                 layer_id in_layer_id = RenderLayer::INVALID_LAYER);
  //
  //
  //
  bool isRunning() const;
  //
  //
  //
  sf::RenderTarget &getRenderTarget();
  //
  //
  //
  Camera &getMainCamera();
  //
  //
  //
  layer_id getBackgroundLayer() const;
  //
  //
  //
  layer_id getShadowLayer() const;
  //
  //
  //
  Keyboard &getDefaultKeyboard();
  //
  //
  //
  Gamepad &getDefaultGamepad();

 private:
  Window window;
  Keyboard default_keyboard;
  Gamepad gamepad1;
  Camera camera;
  sf::View hud_view{sf::FloatRect{0, 0, 800, 600}};
  std::map<int, RenderLayer> render_layers;
  RenderLayer hud_layer;
  std::vector<Entity *> entities;
  Debug debug_gui;
  float dt = 0.01F;
  bool running = true;
  layer_id background_layer = RenderLayer::INVALID_LAYER;
  layer_id shadow_layer = RenderLayer::INVALID_LAYER;
  //
  //
  //
  void toggle_debg(bool in_keep_on = false);
  //
  //
  //
  void poll_input_devices();
};
}  // namespace Engine
