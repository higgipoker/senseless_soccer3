#include "input.hpp"

#include <iostream>

#include <SFML/Window/Event.hpp>

// todo separate out into input / gamepad / keyboard

static const bool DO_POLL_EVENT = false;

// -----------------------------------------------------------------------------
// handle_input
// -----------------------------------------------------------------------------
void handle_input(Game &game, Camera &camera) {
  if (DO_POLL_EVENT) {
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
  } else {
    sf::Joystick::update();
  }
  update_keyboard(game);
  poll_controllers();
  update_controlled_entities();
}

/// map button id's to string identifiers
inline std::map<int, std::string> buttons{
    {0, "A"},     {1, "B"},       {2, "X"},        {3, "Y"},     {4, "LB"},
    {5, "RB"},    {6, "LTRIGER"}, {7, "RTRIGGER"}, {8, "BACK"},  {9, "START"},
    {10, "XBOX"}, {11, "LCKICK"}, {12, "RCLICK"},  {13, "Left"}, {14, "Right"},
    {15, "Up"},   {16, "Down"},
};

void init_event(ControllerEvent &controller, ControllerEventID id,
                ControllerEventStatus status, int param) {
  controller.id = id;
  controller.status = status;
  controller.param = param;
}

void init_gamepad(Gamepad &gamepad) {
  memset(gamepad.device.states, 0, sizeof(gamepad.device.states));
}

bool isConnected(Gamepad &gamepad) {
  if (gamepad.sf_joystick_index <= sf::Joystick::Count)
    return sf::Joystick::isConnected(gamepad.sf_joystick_index);

  return false;
}

bool A(Gamepad &gamepad) {
  return sf::Joystick::isButtonPressed(gamepad.sf_joystick_index, 0);
}

bool B(Gamepad &gamepad) {
  return sf::Joystick::isButtonPressed(gamepad.sf_joystick_index, 1);
}

bool X(Gamepad &gamepad) {
  return sf::Joystick::isButtonPressed(gamepad.sf_joystick_index, 2);
}

bool Y(Gamepad &gamepad) {
  return sf::Joystick::isButtonPressed(gamepad.sf_joystick_index, 3);
}

bool LeftBumper(Gamepad &gamepad) {
  return sf::Joystick::isButtonPressed(gamepad.sf_joystick_index, 4);
}

bool RightBumper(Gamepad &gamepad) {
  return sf::Joystick::isButtonPressed(gamepad.sf_joystick_index, 5);
}

bool LeftTriggerPressed(Gamepad &gamepad) {
  return sf::Joystick::isButtonPressed(gamepad.sf_joystick_index, 6);
}

bool RightTriggerPressed(Gamepad &gamepad) {
  return sf::Joystick::isButtonPressed(gamepad.sf_joystick_index, 7);
}

bool Back(Gamepad &gamepad) {
  return sf::Joystick::isButtonPressed(gamepad.sf_joystick_index, 8);
}

bool Start(Gamepad &gamepad) {
  return sf::Joystick::isButtonPressed(gamepad.sf_joystick_index, 9);
}

bool XboxButton(Gamepad &gamepad) {
  return sf::Joystick::isButtonPressed(gamepad.sf_joystick_index, 10);
}

bool LeftThumbstickClick(Gamepad &gamepad) {
  return sf::Joystick::isButtonPressed(gamepad.sf_joystick_index, 11);
}

bool RightThumbstickClick(Gamepad &gamepad) {
  return sf::Joystick::isButtonPressed(gamepad.sf_joystick_index, 12);
}

bool DpadLeft(Gamepad &gamepad) {
  return sf::Joystick::getAxisPosition(gamepad.sf_joystick_index,
                                       sf::Joystick::Axis::PovX) < 0;
}

bool DpadRight(Gamepad &gamepad) {
  return sf::Joystick::getAxisPosition(gamepad.sf_joystick_index,
                                       sf::Joystick::Axis::PovX) > 0;
}

bool DpadUp(Gamepad &gamepad) {
  return sf::Joystick::getAxisPosition(gamepad.sf_joystick_index,
                                       sf::Joystick::Axis::PovY) < 0;
}

bool DpadDown(Gamepad &gamepad) {
  return sf::Joystick::getAxisPosition(gamepad.sf_joystick_index,
                                       sf::Joystick::Axis::PovY) > 0;
}

float LeftTriggerValue(Gamepad &gamepad) {
  return sf::Joystick::getAxisPosition(gamepad.sf_joystick_index,
                                       sf::Joystick::Z);
}

float RightTriggerValue(Gamepad &gamepad) {
  return sf::Joystick::getAxisPosition(gamepad.sf_joystick_index,
                                       sf::Joystick::R);
}

bool LeftTrigger(Gamepad &gamepad) {
  return LeftTriggerValue(gamepad) > gamepad.trigger_threshold;
}

bool RightTrigger(Gamepad &gamepad) {
  return RightTriggerValue(gamepad) > gamepad.trigger_threshold;
}

sf::Vector2f LeftThumbstick(Gamepad &gamepad) {
  return {
      sf::Joystick::getAxisPosition(gamepad.sf_joystick_index, sf::Joystick::X),
      sf::Joystick::getAxisPosition(gamepad.sf_joystick_index,
                                    sf::Joystick::Y)};
}

sf::Vector2f RightThumbstick(Gamepad &gamepad) {
  return {
      sf::Joystick::getAxisPosition(gamepad.sf_joystick_index, sf::Joystick::U),
      sf::Joystick::getAxisPosition(gamepad.sf_joystick_index,
                                    sf::Joystick::V)};
}

bool UniUp(Gamepad &gamepad) {
  return DpadUp(gamepad) ||
         LeftThumbstick(gamepad).y < -gamepad.thumbstick_threshold;
}

bool UniDown(Gamepad &gamepad) {
  return DpadDown(gamepad) ||
         LeftThumbstick(gamepad).y > gamepad.thumbstick_threshold;
}

bool UniLeft(Gamepad &gamepad) {
  return DpadLeft(gamepad) ||
         LeftThumbstick(gamepad).x < -gamepad.thumbstick_threshold;
}

bool UniRight(Gamepad &gamepad) {
  return DpadRight(gamepad) ||
         LeftThumbstick(gamepad).x > gamepad.thumbstick_threshold;
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void update_keyboard(Game &game) {
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
    if (game.window.hasFocus()) {
      game.game_running = false;
    }
  }

  keyboard.device.states[InputState::Left] =
      keyboard.device.states[InputState::Right] =
          keyboard.device.states[InputState::Up] =
              keyboard.device.states[InputState::Down] = 0;

  if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
    keyboard.device.states[InputState::Left] = 1;
  } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
    keyboard.device.states[InputState::Right] = 1;
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
    keyboard.device.states[InputState::Up] = 1;
  } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
    keyboard.device.states[InputState::Down] = 1;
  }
}

void update_gamepad(Gamepad &gamepad) {
  // //////////////////////////////////////////////////////
  //
  // test
  //
  // //////////////////////////////////////////////////////
  //  unsigned int buttonCount = sf::Joystick::getButtonCount(0);
  //  for (auto i = 0; i < buttonCount; ++i) {
  //    if (sf::Joystick::isButtonPressed(0, i)) {
  //      std::cout << i << std::endl;
  //    }
  //  }

  gamepad.sf_joystick_index = 0;

  if (DpadUp(gamepad)) {
    std::cout << "up" << std::endl;
  }
  if (DpadDown(gamepad)) {
    std::cout << "down" << std::endl;
  }
  if (DpadLeft(gamepad)) {
    std::cout << "left" << std::endl;
  }
  if (DpadRight(gamepad)) {
    std::cout << "right" << std::endl;
  }

  // for comparison for events (chaged statuses)
  int old_states[InputState::Totalevents] = {
      gamepad.device.states[0], gamepad.device.states[1],
      gamepad.device.states[2], gamepad.device.states[3],
      gamepad.device.states[4], gamepad.device.states[5],
      gamepad.device.states[6], gamepad.device.states[7],
      gamepad.device.states[8], gamepad.device.states[9],
      gamepad.device.states[10]};

  // fire button
  gamepad.device.states[InputState::FireUp] = 0;
  if (A(gamepad) || B(gamepad) || X(gamepad) || Y(gamepad)) {
    if (gamepad.device.states[InputState::FireDown] == 0) {
      gamepad.device.states[InputState::FireDown] = 1;
      gamepad.device.fire_ticks = 0;
    } else {
      gamepad.device.states[InputState::FireLength] =
          gamepad.device.fire_ticks++;
    }
  }

  else if (gamepad.device.states[InputState::FireDown] == 1) {
    gamepad.device.states[InputState::FireUp] = 1;
    gamepad.device.states[InputState::FireDown] = 0;
    gamepad.device.states[InputState::FireLengthCached] =
        gamepad.device.fire_ticks;
    gamepad.device.states[InputState::FireLength] = 0;
  }

  // directions
  gamepad.device.states[InputState::Up] =
      gamepad.device.states[InputState::Down] =
          gamepad.device.states[InputState::Left] =
              gamepad.device.states[InputState::Right] = 0;

  if (UniUp(gamepad)) {
    gamepad.device.states[InputState::Up] = 1;
  }

  if (UniDown(gamepad)) {
    gamepad.device.states[InputState::Down] = 1;
  }

  if (UniLeft(gamepad)) {
    gamepad.device.states[InputState::Left] = 1;
  }

  if (UniRight(gamepad)) {
    gamepad.device.states[InputState::Right] = 1;
    std::cout << "right" << std::endl;
  }

  //
  // Fire event
  //
  if (gamepad.device.cached_tap) {
    if (++gamepad.device.ticks_since_tap > fire_double_tap_length) {
      gamepad.device.cached_tap = false;
      gamepad.device.ticks_since_tap = 0;
      std::cout << "tap" << std::endl;
    }
  }
  if (old_states[InputState::FireDown]) {
    if (gamepad.device.states[InputState::FireUp]) {
      if (gamepad.device.states[InputState::FireLengthCached] <=
          fire_tap_length) {
        gamepad.device.ticks_since_tap = 0;
        if (gamepad.device.cached_tap) {
          std::cout << "==========" << std::endl;
          std::cout << "double tap" << std::endl;
          std::cout << "==========" << std::endl;
          gamepad.device.cached_tap = false;
        } else {
          gamepad.device.cached_tap = true;
        }

      } else {
        std::cout << "fire released" << std::endl;
      }
    }

  } else {
    if (gamepad.device.states[InputState::FireDown]) {
      std::cout << "fire pressed" << std::endl;
    }
  }
}

void poll_controllers() {
  for (auto &gamepad : gamepads) {
    update_gamepad(*gamepad);
  }
}
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

void reset_device(InputDevice &device) {}