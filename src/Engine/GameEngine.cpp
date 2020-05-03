#include "GameEngine.hpp"
//
#include <SFML/Window/Event.hpp>
#include <cassert>
#include <iostream>

#include "Vector.hpp"

namespace Senseless {
//
//
//
static const bool NotSortable = false;
static const bool Sortable = true;
//
//
//
GameEngine::GameEngine(const std::string &in_window_title, float in_window_width,
                       float in_window_height, int in_flags, bool in_fullscreen)
    : window(in_window_title, in_window_width, in_window_height, in_flags, in_fullscreen),
      camera(in_window_width, in_window_height),
      debug_gui(window),
      picker(window, entities, debug_gui) {
  // setup the hud view
  hud_view.setSize(in_window_width, in_window_height);
  hud_view.setCenter(in_window_width / 2, in_window_height / 2);
  // setup the camera
  camera.movable.position = {in_window_width / 2, in_window_height / 2};
  camera.setHeight(50);
  addEntity(camera);
  addControllable(camera);
  // set up the render layers
  background_layer = addLayer(NotSortable);
  shadow_layer = addLayer(NotSortable);
  default_layer = addLayer(Sortable);
  // for fps
  last_time = clock.getElapsedTime().asSeconds();
}
//
//
//
GameEngine::~GameEngine() { window.close(); }
//
//
//
void GameEngine::step() noexcept {
  ++frame_counter;

  {  // calc fps
    float current_time = clock.getElapsedTime().asSeconds();
    frames++;
    if (current_time - last_time >= 1.0F) {
      frametime = 1000 / frames;
      frames = 0;
      last_time += 1.0;
    }
  }

  {  // handle input
    if (window.hasFocus()) {
      poll_input_devices();
      for (const auto &controllable : controllables) {
        controllable->handleInput();
      }
    }
  }

  {  // update entities
    camera.update();
    for (const auto &entity : entities) {
      entity->movable.step(dt);
    }
  }

  {  // render
    window.clear({18, 60, 10});
    window.setView(camera.getview());

    // entity layers
    for (auto &layer : render_layers) {
      // sort the layer
      if (layer.second.sortable) {
        std::sort(std::begin(layer.second.sprite_list), std::end(layer.second.sprite_list),
                  [](sf::Drawable *d1, sf::Drawable *d2) -> bool { return d1->z < d2->z; });
      }
      // render the layer
      for (const auto &drawable : layer.second.sprite_list) {
        drawable->perspectivize(camera.getHeight());
        drawable->draw(window);
      }
    }

    //  render hud
    window.setView(hud_view);
    for (const auto &drawable : hud.sprite_list) {
      drawable->draw(window);
    }

    // render debug
    if (Debug::showHud()) {
      window.setView(hud_view);
      debug_gui.prep(frame_counter, frametime);
      debug_gui.draw();
      window.setView(camera.getview());
      picker.update();
    }
    window.display();
  }
}
//
//
//
int GameEngine::addLayer(const bool in_sortable) noexcept {
  const int new_id = render_layers.size();
  render_layers.insert({new_id, RenderLayer(in_sortable)});
  return new_id;
}
//
//
//
void GameEngine::add_sprite(Sprite &in_sprite, layer_id in_layer_id) noexcept {
  if (in_layer_id == RenderLayer::HUD_LAYER) {
    hud.sprite_list.push_back(&in_sprite);
    return;
  }

  if (render_layers.empty()) {
    std::cout << "addDrawable> no layers" << std::endl;
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
      std::cout << "addRenderable> Tried to add to non existent layer: " << in_layer_id
                << std::endl;
    }
  }
}
//
//
//
void GameEngine::addControllable(Controllable &in_controllable) noexcept {
  controllables.insert(&in_controllable);
}
//
//
//
void GameEngine::addEntity(Entity &in_entity, layer_id in_layer_id) noexcept {
  if (in_layer_id == getHudLayer()) {
    in_entity.movable.is_hud = true;
  }

  add_sprite(in_entity.getSprite(), in_layer_id);

  if (in_entity.hasShadow()) {
    add_sprite(in_entity.getShadow(), shadow_layer);
  }
  entities.insert(&in_entity);
}
//
//
//
bool GameEngine::isRunning() const noexcept { return running; }
//
//
//
sf::RenderTarget &GameEngine::getRenderTarget() noexcept { return window; }
//
//
//
Camera &GameEngine::getMainCamera() noexcept { return camera; }
//
//
//
layer_id GameEngine::getHudLayer() const noexcept { return hud_layer; }
//
//
//
layer_id GameEngine::getBackgroundLayer() const noexcept { return background_layer; }
//
//
//
layer_id GameEngine::getDefaultLayer() const noexcept { return default_layer; }
//
//
//
layer_id GameEngine::getShadowLayer() const noexcept { return shadow_layer; }
//
//
//
Keyboard &GameEngine::getDefaultKeyboard() noexcept { return default_keyboard; }
//
//
//
Gamepad &GameEngine::getDefaultGamepad() noexcept { return gamepad1; }
//
//
//
void GameEngine::toggle_debug(bool in_keep_on) noexcept {
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
void GameEngine::poll_input_devices() noexcept {
  static sf::Event event;
  while (window.pollEvent(event)) {
#ifndef NDEBUG
    if (Debug::showHud()) {
      debug_gui.handleInput(event);
      picker.handleInput(event);
    }
#endif
    switch (event.type) {
      case sf::Event::KeyPressed:
        if (window.hasFocus()) {
          if (event.key.code == sf::Keyboard::Tab) {
            toggle_debug();
          } else if (event.key.code == sf::Keyboard::Escape) {
#ifndef NDEBUG
            if (Debug::showHud()) {
              toggle_debug();
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
      case sf::Event::Resized: {
        // update the view to the new size of the window
        // update the view to the new size of the window
        sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
        hud_view = sf::View(visibleArea);
      } break;
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
}  // namespace Senseless
