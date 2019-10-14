#include "GameEngine.hpp"

#include "Vector.hpp"

#include <SFML/Window/Event.hpp>

#include <cassert>
#include <iostream>

namespace Engine {
//
//
//
inline struct {
  bool operator()(const sf::Drawable *d1, const sf::Drawable *d2) const {
    return d1->z < d2->z;
  }
} sort_drawable;
//
//
//
GameEngine::GameEngine(const std::string &in_window_title, int in_window_width,
                       int in_window_height, int in_flags, bool in_fullscreen)
    : window(in_window_title, in_window_width, in_window_height, in_flags,
             in_fullscreen),
      debug_gui(window) {
  camera.movable.setPosition({static_cast<float>(in_window_width) / 2,
                              static_cast<float>(in_window_height) / 2});
  background_layer = addLayer(false);
  shadow_layer = addLayer(false);
  camera.setHeight(50);
  camera.attachInput(default_keyboard);
  entities.push_back(&camera);
}
//
//
//
GameEngine::~GameEngine() { window.close(); }
//
//
//
void GameEngine::step() {
  handle_input();
  update_entities();
  render();
}
//
//
//
int GameEngine::addLayer(bool in_sortable) {
  const int new_id = render_layers.size();
  render_layers.insert({new_id, RenderLayer(in_sortable)});
  return new_id;
}
//
//
//
void GameEngine::addDrawable(sf::Drawable &in_drawable, layer_id in_layer_id) {
  if (render_layers.empty()) {
    std::cout << "Engine::addDrawable> no layers" << std::endl;
    return;
  }
  if (in_layer_id == RenderLayer::INVALID_LAYER) {
    // add to last layer
    render_layers.at(render_layers.size() - 1)
        .draw_list.push_back(&in_drawable);
  } else {
    // add to specified layer
    if (in_layer_id < render_layers.size()) {
      render_layers.at(in_layer_id).draw_list.push_back(&in_drawable);
    } else {
      std::cout << "Engine::addRenderable> Tried to add to non existent layer: "
                << in_layer_id << std::endl;
    }
  }
}
//
//
//
void GameEngine::addEntity(Entity &in_entity, layer_id in_layer_id) {
  addDrawable(in_entity.sprite, in_layer_id);
  addDrawable(in_entity.shadow, shadow_layer);
  entities.push_back(&in_entity);
}
//
//
//
void GameEngine::handle_input() {
  static sf::Event event;
  while (window.pollEvent(event)) {
    default_keyboard.update(event);
    if (Debug::showHud()) {
      debug_gui.pollEvent(event);
    }
    switch (event.type) {
      case sf::Event::KeyPressed:
        if (window.hasFocus()) {
          if (event.key.code == sf::Keyboard::Tab) {
#ifndef NDEBUG
            Debug::toggle();
#endif
          } else if (event.key.code == sf::Keyboard::Escape) {
#ifndef NDEBUG
            if (Debug::showHud()) {
              Debug::toggle();
            }
#endif
            else {
              running = false;
            }
          }
        }
        break;
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
bool GameEngine::isRunning() const { return running; }
//
//
//
void GameEngine::sort_drawables() {
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
sf::RenderTarget &GameEngine::getRenderTarget() { return window; }
//
//
//
Camera &GameEngine::getMainCamera() { return camera; }
//
//
//
void GameEngine::update_entities() {
  // entities
  for (auto &entity : entities) {
    entity->handleInput();
    entity->update();
    entity->movable.step(dt);
    entity->perspectivize(camera.movable.getZ());
  }
}
//
//
//
void GameEngine::render() {
  window.clear(sf::Color::Blue);
  render_entities();
  render_hud();
  render_debug();
  window.display();
}
//
//
//
void GameEngine::render_entities() {
  sort_drawables();
  window.setView(camera.getview());
  for (auto &layer : render_layers) {
    for (auto &drawable : layer.second.draw_list) {
      window.draw(*drawable);
    }
  }
}
//
//
//
void GameEngine::render_hud() {
  window.setView(hud_view);
  for (auto &drawable : hud_layer.draw_list) {
    window.draw(*drawable);
  }
}
//
//
//
void GameEngine::render_debug() {
  if (Debug::showHud()) {
    debug_gui.update();
  }
}
//
//
//
layer_id GameEngine::getBackgroundLayer() const { return background_layer; }
//
//
//
layer_id GameEngine::getShadowLayer() const { return shadow_layer; }
//
//
//
Keyboard &GameEngine::getDefaultKeyboard() { return default_keyboard; }
}  // namespace Engine
