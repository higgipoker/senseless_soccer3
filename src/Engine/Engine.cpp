#include "Engine.hpp"

#include "includes.hpp"

#include <SFML/Window/Event.hpp>

#include <cassert>

namespace Engine {
//
// sort predicate for drawables
//
inline struct {
  bool operator()(const sf::Drawable *d1, const sf::Drawable *d2) const {
    return d1->z < d2->z;
  }
} sort_drawable;
//
//
//
Engine::Engine(const std::string &in_window_title, int in_window_width,
               int in_window_height, int in_flags, bool in_fullscreen)
    : window(in_window_title, in_window_width, in_window_height, in_flags,
             in_fullscreen),
      debug_gui(window) {
  camera.movable.position.x = static_cast<float>(in_window_width) / 2;
  camera.movable.position.y = static_cast<float>(in_window_height) / 2;
  // set up a layer for bg
  background_layer = addLayer(false);
  // set up a layer for shadows
  shadow_layer = addLayer(false);
  // camera should always be the first entity
  entities.push_back(&camera);
}
//
//
//
Engine::~Engine() { window.close(); }
//
//
//
void Engine::step() {
  // input
  poll_window();

  // entities
  for (auto &entity : entities) {
    entity->movable.step(dt);
    entity->perspectivize(camera.height);
    entity->update();
  }

  // render
  window.clear(sf::Color::Blue);

  // normal drawables
  sort_drawables();
  window.setView(camera.view);
  for (auto &layer : render_layers) {
    for (auto &drawable : layer.second.draw_list) {
      window.draw(*drawable);
    }
  }

  // hud elements
  window.setView(hud_view);
  for (auto &drawable : hud_layer.draw_list) {
    window.draw(*drawable);
  }

#ifndef NDEBUG
  // imgui debug ui
  if (Debug::show_debug_hud) {
    debug_gui.update();
  }
#endif

  window.display();
}
//
//
//
int Engine::addLayer(bool in_sortable) {
  const int new_id = render_layers.size();
  render_layers.insert({new_id, RenderLayer(in_sortable)});
  return new_id;
}
//
//
//
void Engine::addDrawable(sf::Drawable &in_drawable, layer_id in_layer_id) {
  if (render_layers.empty()) {
    std::cout << "Engine::addDrawable> no layers" << std::endl;
    return;
  }
  if (in_layer_id == RenderLayer::INVALID_LAYER) {
    // add to last layer
    render_layers.at(render_layers.size() - 1)
        .draw_list.emplace_back(&in_drawable);
  } else {
    // add to specified layer
    if (in_layer_id < render_layers.size()) {
      render_layers.at(in_layer_id).draw_list.emplace_back(&in_drawable);
    } else {
      std::cout << "Engine::addRenderable> Tried to add to non existent layer: "
                << in_layer_id << std::endl;
    }
  }
}
//
//
//
void Engine::addEntity(Entity &in_entity, layer_id in_layer_id) {
  addDrawable(in_entity.sprite, in_layer_id);
  addDrawable(in_entity.shadow, shadow_layer);
  entities.emplace_back(&in_entity);
}
//
//
//
void Engine::poll_window() {
  static sf::Event event;
  while (window.pollEvent(event)) {
    if (Debug::show_debug_hud) {
      debug_gui.pollEvent(event);
    }
    switch (event.type) {
      case sf::Event::Closed:
        running = false;
        break;
      case sf::Event::Resized:
        break;
      case sf::Event::LostFocus:
        break;
      case sf::Event::GainedFocus:
        break;
      case sf::Event::TextEntered:
        break;
      case sf::Event::KeyPressed:
        if (window.hasFocus()) {
          if (event.key.code == sf::Keyboard::Escape) {
            if (Debug::show_debug_hud) {
              Debug::show_debug_hud = !Debug::show_debug_hud;
            } else {
              running = false;
            }
          } else if (event.key.code == sf::Keyboard::Tab) {
            Debug::show_debug_hud = !Debug::show_debug_hud;
          }
        }
        break;
      case sf::Event::KeyReleased:
        break;
      case sf::Event::MouseWheelMoved:
        break;
      case sf::Event::MouseWheelScrolled:
        break;
      case sf::Event::MouseButtonPressed:
        break;
      case sf::Event::MouseButtonReleased:
        break;
      case sf::Event::MouseMoved:
        break;
      case sf::Event::MouseEntered:
        break;
      case sf::Event::MouseLeft:
        break;
      case sf::Event::JoystickButtonPressed:
        break;
      case sf::Event::JoystickButtonReleased:
        break;
      case sf::Event::JoystickMoved:
        break;
      case sf::Event::JoystickConnected:
        break;
      case sf::Event::JoystickDisconnected:
        break;
      case sf::Event::TouchBegan:
        break;
      case sf::Event::TouchMoved:
        break;
      case sf::Event::TouchEnded:
        break;
      case sf::Event::SensorChanged:
        break;
      case sf::Event::Count:
        break;
    }
  }
}
//
//
//
bool Engine::isRunning() { return running; }
//
//
//
void Engine::sort_drawables() {
  for (auto &layer : render_layers) {
    if (layer.second.sortable) {
      std::sort(layer.second.draw_list.begin(), layer.second.draw_list.end(),
                sort_drawable);
    }
  }
}
//
//
//
sf::RenderTarget &Engine::getRenderTarget() { return window; }
//
//
//
Camera &Engine::getMainCamera() { return camera; }
//
//
//
Entity Engine::makeEntity(Sprite &in_sprite, Sprite &in_shadow) {
  return Entity(in_sprite, in_shadow);
}
}  // namespace Engine
