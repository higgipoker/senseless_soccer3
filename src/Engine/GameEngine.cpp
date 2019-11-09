#include "GameEngine.hpp"

#include <SFML/Window/Event.hpp>
#include <cassert>
#include <iostream>

#include "Vector.hpp"

namespace Engine {
//
//
//
GameEngine::GameEngine(const std::string &in_window_title, int in_window_width,
                       int in_window_height, int in_flags, bool in_fullscreen)
    : window(in_window_title, in_window_width, in_window_height, in_flags,
             in_fullscreen),
      camera(in_window_width, in_window_height),
      debug_gui(window) {
  camera.movable.position = {static_cast<float>(in_window_width) / 2,
                             static_cast<float>(in_window_height) / 2};
  background_layer = addLayer(false);
  shadow_layer = addLayer(false);
  default_layer = addLayer(false);
  camera.setHeight(50);
  addEntity(camera);

  last_time = clock.getElapsedTime().asSeconds();
}
//
//
//
GameEngine::~GameEngine() { window.close(); }
//
//
//
void GameEngine::step() {
  ++frame_counter;

  // fps
  float current_time = clock.getElapsedTime().asSeconds();
  frames++;
  if (current_time - last_time >= 1.0) {
    frametime = 1000 / frames;
    frames = 0;
    last_time += 1.0;
  }

  // handle input
  poll_input_devices();
  for (const auto &controllable : controllables) {
    controllable->handleInput();
  }

  // update entities
  for (const auto &movable : movables) {
    movable->step(dt);
  }

  // sort renderables
  for (auto &layer : render_layers) {
    if (layer.second.sortable) {
      std::sort(std::begin(layer.second.sprite_list),
                std::end(layer.second.sprite_list),
                [](sf::Drawable *d1, sf::Drawable *d2) -> bool {
                  return d1->z < d2->z;
                });
    }
  }

  // render
  window.clear(sf::Color::Red);
  getMainCamera().update();
  window.setView(camera.getview());

  // render entities
  for (const auto &layer : render_layers) {
    for (const auto &drawable : layer.second.sprite_list) {
      drawable->perspectivize(camera.getHeight());
      window.draw(*drawable);
    }
  }

  // render hud
  window.setView(hud_view);
  for (const auto &drawable : hud_layer.sprite_list) {
    window.draw(*drawable);
  }

  // render debug
  if (Debug::showHud()) {
    window.setView(hud_view);
    debug_gui.update(frame_counter, frametime);
  }

  window.display();
  window.setView(camera.getview());
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
void GameEngine::addSprite(Sprite &in_sprite, layer_id in_layer_id) {
  if (render_layers.empty()) {
    std::cout << "Engine::addDrawable> no layers" << std::endl;
    return;
  }
  if (in_layer_id == RenderLayer::INVALID_LAYER) {
    // add to default layer
    render_layers.at(default_layer).sprite_list.push_back(&in_sprite);
  } else {
    // add to specified layer
    if (in_layer_id < render_layers.size()) {
      render_layers.at(in_layer_id).sprite_list.push_back(&in_sprite);
    } else {
      std::cout << "Engine::addRenderable> Tried to add to non existent layer: "
                << in_layer_id << std::endl;
    }
  }
}
//
//
//
void GameEngine::addControllable(Controllable &in_controllable) {
  controllables.insert(&in_controllable);
}
//
//
//
void GameEngine::addEntity(Entity &in_entity, layer_id in_layer_id) {
  addSprite(in_entity.getSprite(), in_layer_id);
  addSprite(in_entity.getShadow(), shadow_layer);
  movables.insert(&in_entity.movable);
}
//
//
//
bool GameEngine::isRunning() const { return running; }
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
layer_id GameEngine::getBackgroundLayer() const { return background_layer; }
//
//
//
layer_id GameEngine::getDefaultLayer() const { return default_layer; }
//
//
//
layer_id GameEngine::getShadowLayer() const { return shadow_layer; }
//
//
//
Keyboard &GameEngine::getDefaultKeyboard() { return default_keyboard; }
//
//
//
Gamepad &GameEngine::getDefaultGamepad() { return gamepad1; }
//
//
//
void GameEngine::toggle_debg(bool in_keep_on) {
#ifndef NDEBUG
  if (in_keep_on) {
    Debug::show();
  } else {
    Debug::toggle();
  }
#endif
}
//
//
//
void GameEngine::poll_input_devices() {
  static sf::Event event;
  while (window.pollEvent(event)) {
    if (Debug::showHud()) {
      debug_gui.handleInput(event);
    }
    switch (event.type) {
      case sf::Event::KeyPressed:
        if (window.hasFocus()) {
          if (event.key.code == sf::Keyboard::Tab) {
            toggle_debg();
          } else if (event.key.code == sf::Keyboard::Escape) {
#ifndef NDEBUG
            if (Debug::showHud()) {
              toggle_debg();
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
  default_keyboard.update();
  gamepad1.update();
}
}  // namespace Engine
