#include "input.hpp"
#include "gamepad.hpp"
#include "keyboard.hpp"

#include <iostream>

#include <SFML/Window/Event.hpp>

// todo separate out into input / gamepad / keyboard

// -----------------------------------------------------------------------------
// handle_input
// -----------------------------------------------------------------------------
void handle_input(Game &game, Camera &camera) {
  static sf::Event event;
  while (game.window.pollEvent(event)) {
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
  update_keyboard();
  // poll_controllers();
  update_controlled_entities();
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void init_event(ControllerEvent &controller, ControllerEventID id,
                ControllerEventStatus status, int param) {
  controller.id = id;
  controller.status = status;
  controller.param = param;
}
// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void update_controlled_entities() {
  for (auto &entry : controlled_entities) {
    if (entry.second->states[InputState::Left]) {
      apply_force(*entry.first, gamelib3::Vector3(-1, 0));
    }
    if (entry.second->states[InputState::Right]) {
      apply_force(*entry.first, gamelib3::Vector3(1, 0));
    }
    if (entry.second->states[InputState::Up]) {
      apply_force(*entry.first, gamelib3::Vector3(0, -1));
    }
    if (entry.second->states[InputState::Down]) {
      apply_force(*entry.first, gamelib3::Vector3(0, 1));
    }
  }
}
// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
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
// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void poll_controllers() {
  for (auto &gamepad : gamepads) {
    update_gamepad(*gamepad);
  }
}
