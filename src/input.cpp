#include "input.hpp"
#include <iostream>

#include <SFML/Window/Event.hpp>

// todo separate out into input / gamepad / keyboard

static const bool DO_POLL_EVENT = true;

// -----------------------------------------------------------------------------
// handle_input
// -----------------------------------------------------------------------------
void handle_input(Game &game) {
  if (DO_POLL_EVENT) {
    static sf::Event event;
    while (game.window.pollEvent(event)) {
      switch (event.type) {
        case sf::Event::Closed:
          game.game_running = false;
          break;
        case sf::Event::Resized:
          game.camera.setSize(event.size.width, event.size.height);
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

void init(Gamepad &gamepad) {
  memset(gamepad.states, 0, sizeof(gamepad.states));
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
  return sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::PovX) < 0;
}

bool DpadRight(Gamepad &gamepad) {
  return sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::PovX) > 0;
}

bool DpadUp(Gamepad &gamepad) {
  return sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::PovY) < 0;
}

bool DpadDown(Gamepad &gamepad) {
  return sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::PovY) > 0;
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

void update(Gamepad &gamepad) {
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
      gamepad.states[0], gamepad.states[1], gamepad.states[2],
      gamepad.states[3], gamepad.states[4], gamepad.states[5],
      gamepad.states[6], gamepad.states[7], gamepad.states[8],
      gamepad.states[9], gamepad.states[10]};

  // fire button
  gamepad.states[InputState::FireUp] = 0;
  if (A(gamepad) || B(gamepad) || X(gamepad) || Y(gamepad)) {
    if (gamepad.states[InputState::FireDown] == 0) {
      gamepad.states[InputState::FireDown] = 1;
      gamepad.fire_ticks = 0;
    } else {
      gamepad.states[InputState::FireLength] = gamepad.fire_ticks++;
    }
  }

  else if (gamepad.states[InputState::FireDown] == 1) {
    gamepad.states[InputState::FireUp] = 1;
    gamepad.states[InputState::FireDown] = 0;
    gamepad.states[InputState::FireLengthCached] = gamepad.fire_ticks;
    gamepad.states[InputState::FireLength] = 0;
  }

  // directions
  gamepad.states[InputState::Up] = gamepad.states[InputState::Down] =
      gamepad.states[InputState::Left] = gamepad.states[InputState::Right] = 0;

  if (UniUp(gamepad)) {
    gamepad.states[InputState::Up] = 1;
  }

  if (UniDown(gamepad)) {
    gamepad.states[InputState::Down] = 1;
  }

  if (UniLeft(gamepad)) {
    gamepad.states[InputState::Left] = 1;
  }

  if (UniRight(gamepad)) {
    gamepad.states[InputState::Right] = 1;
    std::cout << "right" << std::endl;
  }

  //
  // Fire event
  //
  if (gamepad.cached_tap) {
    if (++gamepad.ticks_since_tap > fire_double_tap_length) {
      gamepad.cached_tap = false;
      gamepad.ticks_since_tap = 0;
      std::cout << "tap" << std::endl;
    }
  }
  if (old_states[InputState::FireDown]) {
    if (gamepad.states[InputState::FireUp]) {
      if (gamepad.states[InputState::FireLengthCached] <= fire_tap_length) {
        gamepad.ticks_since_tap = 0;
        if (gamepad.cached_tap) {
          std::cout << "==========" << std::endl;
          std::cout << "double tap" << std::endl;
          std::cout << "==========" << std::endl;
          gamepad.cached_tap = false;
        } else {
          gamepad.cached_tap = true;
        }

      } else {
        std::cout << "fire released" << std::endl;
      }
    }

  } else {
    if (gamepad.states[InputState::FireDown]) {
      std::cout << "fire pressed" << std::endl;
    }
  }
}
