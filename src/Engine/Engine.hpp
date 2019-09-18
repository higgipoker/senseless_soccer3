#pragma once

#include "Camera.hpp"
#include "Movable.hpp"
#include "Sprite.hpp"
#include "Window.hpp"
#include "Entity.hpp"

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/View.hpp>

#include <map>
#include <vector>

namespace Engine {

/**
 * @brief The RenderLayer struct
 * this allows for only sorting of layers which will change order
 * dynamically. For other layers just add drawable elements in
 * the correct order!
 */
struct RenderLayer {
  RenderLayer(bool in_sortable = false) : sortable(in_sortable) {}
  std::vector<sf::Drawable *> draw_list;
  bool sortable = false;
  static const int INVALID_LAYER = -1;
};

/**
 * @brief The Engine class
 */
class Engine {
 public:
  /**
   * @brief Engine
   */
  Engine(const std::string &in_window_title = "Untitled",
         int in_window_width = 800, int in_window_height = 600,
         int in_flags = sf::Style::Default, bool in_fullscreen = false);
  /**
   *
   */
  ~Engine();
  /**
   * @brief step
   */
  void step();
  /**
   * @brief addLayer
   * @return
   */
  int addLayer(bool in_sortable = false);
  /**
   * @brief addRenderable
   * @param _renderable
   */
  void addDrawable(sf::Drawable *in_drawable,
                   int in_layer_id = RenderLayer::INVALID_LAYER);
  /**
   * @brief addMovable
   * @param _movable
   */
  void addMovable(Movable *in_movable);
  /**
   * @brief remRenderable
   * @param _renderable
   */
  void remDrawable(sf::Drawable *in_drawable,
                   int in_layer_id = RenderLayer::INVALID_LAYER);
  /**
   * @brief remMovable
   * @param _movable
   */
  void remMovable(Movable *in_movable);
  /**
   * @brief addentity
   * @param in_entity
   */
  void addentity(Entity *in_entity);
  /**
   * @brief remEntity
   * @param in_entity
   */
  void remEntity(Entity *in_entity);
  /**
   * @brief isRunning
   * @return
   */
  bool isRunning();
  /**
   * @brief getRenderTarget
   * @return
   */
  sf::RenderTarget &getRenderTarget();
  /**
   * @brief getMainCamera
   * @return
   */
  Camera& getMainCamera();

 private:
  /// wrapper of sf::window
  Window window;
  /// a camera
  Camera camera;
  /// a view for hud elements
  sf::View hud_view;
  /// list of layers to render
  std::map<int, RenderLayer> render_layers;
  /// layer for hud drawables
  RenderLayer hud_layer;
  /// list of physical stuff to integrate
  std::vector<Movable *> movable_list;
  /// integration step
  float dt = 0.01F;
  /// desired framerate
  const int framerate = 60;
  /// app running flag
  bool running = true;
  /**
   * @brief poll_window
   */
  void poll_window();
  /**
   * @brief sort_drawables
   */
  void sort_drawables();
};
}  // namespace Engine
