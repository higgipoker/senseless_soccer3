#include "input.hpp"
#include "data.hpp"
#include "debug.hpp"
#include "gamepad.hpp"
#include "imgui/imgui-SFML.h"
#include "keyboard.hpp"

#include <iostream>

#include <SFML/Window/Event.hpp>
//
// handle_input
//
void handle_input(Game &game, Camera &camera) {
  static sf::Event event;
  while (game.window.pollEvent(event)) {
    if (game.debug) {
      ImGui::SFML::ProcessEvent(event);
    }

    switch (event.type) {
      case sf::Event::Closed:
        game.game_running = false;
        break;
      case sf::Event::Resized:
        camera.view.setSize(event.size.width, event.size.height);
        break;
      case sf::Event::LostFocus:
        break;
      case sf::Event::GainedFocus:
        break;
      case sf::Event::TextEntered:
        break;
      case sf::Event::KeyPressed:
        if (game.window.hasFocus()) {
          if (event.key.code == sf::Keyboard::Escape) {
            game.game_running = false;
          } else if (event.key.code == sf::Keyboard::Tab) {
#ifndef NDEBUG
            toggle_debug();
#endif
          }
        }
        break;
      case sf::Event::KeyReleased:
        break;
      case sf::Event::MouseWheelMoved:
        break;
      case sf::Event::MouseWheelScrolled:
        break;
      case sf::Event::MouseButtonPressed: {
        if (game.debug) {
          if (event.mouseButton.button == sf::Mouse::Left) {
            mouse_pressed = true;
            // get the current mouse position in the window
            sf::Vector2i pixelPos = sf::Mouse::getPosition(game.window);
            // convert it to world coordinates
            sf::Vector2f worldPos = game.window.mapPixelToCoords(pixelPos);
            for (int i = used_entity_count - 1; i >= 0; --i) {
              auto sprite = PLAYER_SPRITE(entity_pool[i]);
              auto bounds = sprite->getGlobalBounds();
              if (bounds.contains(worldPos.x, worldPos.y)) {
                if (entity_pool[i].type != EntityType::Camera &&
                    entity_pool[i].type != EntityType::Background) {
                  grab_entity(i, worldPos.x, worldPos.y);
                }
              }
            }
          }
        }
      } break;
      case sf::Event::MouseButtonReleased:
        if (game.debug) {
          if (event.mouseButton.button == sf::Mouse::Left) {
          }
          mouse_pressed = false;
          release_entity();
        }
        break;
      case sf::Event::MouseMoved:
        if (game.debug) {
          if (mouse_pressed) {
            // get the current mouse position in the window
            sf::Vector2i pixelPos = sf::Mouse::getPosition(game.window);
            // convert it to world coordinates
            sf::Vector2f worldPos = game.window.mapPixelToCoords(pixelPos);
            mouse_dragged(worldPos.x, worldPos.y);
          }
        }
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
  update_keyboard();
  // poll_controllers();
  update_controlled_entities();
}
//
//
//
void init_event(ControllerEvent &controller, ControllerEventID id,
                ControllerEventStatus status, int param) {
  controller.id = id;
  controller.status = status;
  controller.param = param;
}
//
//
//
void update_controlled_entities() {
  static const int f = 50;
  for (auto &entry : controlled_entities) {
    if (entry.second->states[InputState::Left]) {
      apply_force(*entry.first, Vector3(-f, 0));
    }
    if (entry.second->states[InputState::Right]) {
      apply_force(*entry.first, Vector3(f, 0));
    }
    if (entry.second->states[InputState::Up]) {
      apply_force(*entry.first, Vector3(0, -f));
    }
    if (entry.second->states[InputState::Down]) {
      apply_force(*entry.first, Vector3(0, f));
    }
    if (entry.second->states[InputState::FireDown]) {
      apply_force(*entry.first, Vector3(0.f, 0.f, 20.f));
    }
  }
}
//
//
//
std::array<int, MAX_JOYSTICKS> get_joystick_ids() {
  std::array<int, MAX_JOYSTICKS> ids;
  for (int i = 0; i < MAX_JOYSTICKS; ++i) {
    if (sf::Joystick::isConnected(i)) {
      ids[i] = 1;
    } else {
      ids[i] = 0;
    }
  }
  return ids;
}
//
//
//
void poll_controllers() {
  for (auto &gamepad : gamepads) {
    update_gamepad(*gamepad);
  }
}
