#include "Engine.hpp"

#include <SFML/Window/Event.hpp>

#include <cassert>
#include <iostream>

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
  camera.position.x = static_cast<float>(in_window_width) / 2;
  camera.position.y = static_cast<float>(in_window_height) / 2;
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

  // camera
  camera.step(dt);

  // physics
  for (auto &movable : movable_list) {
    movable->step(dt);
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

  // imgui debug ui
  if (show_debug_hud) {
    debug_gui.update();
  }

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
void Engine::addDrawable(sf::Drawable *in_drawable, size_t in_layer_id) {
  if (render_layers.empty()) {
    std::cout << "Engine::addDrawable > no layers" << std::endl;
    return;
  }
  if (in_layer_id == RenderLayer::INVALID_LAYER) {
    // add to last layer
    render_layers.at(render_layers.size() - 1)
        .draw_list.emplace_back(in_drawable);
  } else {
    // add to specified layer
    if (in_layer_id < render_layers.size()) {
      render_layers.at(in_layer_id).draw_list.emplace_back(in_drawable);
    } else {
      std::cout << "Engine::addRenderable >Tried to add to non existent layer: "
                << in_layer_id << std::endl;
    }
  }
}
//
//
//
void Engine::addMovable(Movable *in_movable) {
  movable_list.emplace_back(in_movable);
}
//
//
//
void Engine::remDrawable(sf::Drawable *in_drawable, size_t in_layer_id) {
  // do we know the layer?
  if (in_layer_id != RenderLayer::INVALID_LAYER) {
    if (in_layer_id < render_layers.size()) {
      auto it =
          find(render_layers.at(in_layer_id).draw_list.begin(),
               render_layers.at(in_layer_id).draw_list.begin(), in_drawable);
      if (it != render_layers.at(in_layer_id).draw_list.end()) {
        render_layers.at(in_layer_id).draw_list.erase(it);
      }
    } else {
      std::cout << "Engine::remRenderable > Invalid layer provided: "
                << in_layer_id << std::endl;
    }
  } else {
    // search all layers for the renderable
    bool found = false;
    for (auto &layer : render_layers) {
      auto it = find(layer.second.draw_list.begin(),
                     layer.second.draw_list.end(), in_drawable);
      if (it != layer.second.draw_list.end()) {
        layer.second.draw_list.erase(it);
        found = true;
        break;
      }
    }
    if (!found) {
      std::cout << "Engine::remRenderable > Renderable not found" << std::endl;
    }
  }
}
//
//
//
void Engine::remMovable(Movable *in_movable) {
  auto it = find(movable_list.begin(), movable_list.end(), in_movable);
  if (it != movable_list.end()) {
    movable_list.erase(it);
  }
}
//
//
//
void Engine::addentity(Entity *in_entity) {
  if (auto sprite = in_entity->sprite) {
    addDrawable(sprite);
  }
  if (auto movable = in_entity->movable) {
    addMovable(movable);
  }
}
//
//
//
void Engine::remEntity(Entity *in_entity) {
  if (auto sprite = in_entity->sprite) {
    remDrawable(sprite);
  }
  if (auto movable = in_entity->movable) {
    remMovable(movable);
  }
}
//
//
//
void Engine::poll_window() {
  static sf::Event event;
  while (window.pollEvent(event)) {
    if (show_debug_hud) {
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
            if (show_debug_hud) {
              show_debug_hud = !show_debug_hud;
            } else {
              running = false;
            }
          } else if (event.key.code == sf::Keyboard::Tab) {
            show_debug_hud = !show_debug_hud;
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
  Sprite::draw_bounds = show_debug_hud;
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
}  // namespace Engine
