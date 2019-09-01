#include "gamepad.hpp"
//
//
//
void init_gamepad(Gamepad &gamepad) {
  memset(gamepad.device.states, 0, sizeof(gamepad.device.states));
}
//
//
//
bool isConnected(Gamepad &gamepad) {
  if (gamepad.sf_joystick_index <= sf::Joystick::Count)
    return sf::Joystick::isConnected(gamepad.sf_joystick_index);

  return false;
}
//
//
//
void set_button_mask(Gamepad &gamepad) {
  if (sf::Joystick::isButtonPressed(gamepad.sf_joystick_index, 0)) {
    gamepad.device.buttonmask |= mask_a;
  }

  if (sf::Joystick::isButtonPressed(gamepad.sf_joystick_index, 1)) {
    gamepad.device.buttonmask |= mask_b;
  }

  if (sf::Joystick::isButtonPressed(gamepad.sf_joystick_index, 2)) {
    gamepad.device.buttonmask |= mask_x;
  }

  if (sf::Joystick::isButtonPressed(gamepad.sf_joystick_index, 3)) {
    gamepad.device.buttonmask |= mask_y;
  }

  if (sf::Joystick::isButtonPressed(gamepad.sf_joystick_index, 4)) {
    gamepad.device.buttonmask |= mask_l1;
  }

  if (sf::Joystick::isButtonPressed(gamepad.sf_joystick_index, 5)) {
    gamepad.device.buttonmask |= mask_r1;
  }

  if (sf::Joystick::isButtonPressed(gamepad.sf_joystick_index, 8)) {
    gamepad.device.buttonmask |= mask_back;
  }

  if (sf::Joystick::isButtonPressed(gamepad.sf_joystick_index, 9)) {
    gamepad.device.buttonmask |= mask_start;
  }
}
//
//
//
void set_dpad_mask(Gamepad &gamepad) {
  if (sf::Joystick::getAxisPosition(gamepad.sf_joystick_index,
                                    sf::Joystick::Axis::PovX) < 0) {
    gamepad.device.directionmask |= mask_dpad_left;
  }
  if (sf::Joystick::getAxisPosition(gamepad.sf_joystick_index,
                                    sf::Joystick::Axis::PovX) > 0) {
    gamepad.device.directionmask |= mask_dpad_right;
  }
  if (sf::Joystick::getAxisPosition(gamepad.sf_joystick_index,
                                    sf::Joystick::Axis::PovY) < 0) {
    gamepad.device.directionmask |= mask_dpad_up;
  }
  if (sf::Joystick::getAxisPosition(gamepad.sf_joystick_index,
                                    sf::Joystick::Axis::PovY) > 0) {
    gamepad.device.directionmask |= mask_dpad_down;
  }
}
//
//
//
void set_stick_mask(Gamepad &gamepad) {
  if (sf::Joystick::getAxisPosition(gamepad.sf_joystick_index,
                                    sf::Joystick::Y) <
      -gamepad.thumbstick_threshold) {
    gamepad.device.directionmask |= mask_stick_up;
  }

  if (sf::Joystick::getAxisPosition(gamepad.sf_joystick_index,
                                    sf::Joystick::Y) >
      gamepad.thumbstick_threshold) {
    gamepad.device.directionmask |= mask_stick_down;
  }

  if (sf::Joystick::getAxisPosition(gamepad.sf_joystick_index,
                                    sf::Joystick::X) <
      -gamepad.thumbstick_threshold) {
    gamepad.device.directionmask |= mask_stick_left;
  }

  if (sf::Joystick::getAxisPosition(gamepad.sf_joystick_index,
                                    sf::Joystick::X) >
      gamepad.thumbstick_threshold) {
    gamepad.device.directionmask |= mask_stick_right;
  }
}

//
//
//
void update_gamepad(Gamepad &gamepad) {
  memset(gamepad.device.states, 0, sizeof(gamepad.device.states));
  gamepad.device.buttonmask = mask_zero;
  gamepad.device.directionmask = mask_zero;

  gamepad.sf_joystick_index = 0;
  set_button_mask(gamepad);
  set_dpad_mask(gamepad);
  set_stick_mask(gamepad);

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
  if (gamepad.device.buttonmask & mask_a) {
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

  if ((gamepad.device.directionmask & mask_dpad_up) ||
      (gamepad.device.directionmask & mask_stick_up)) {
    gamepad.device.states[InputState::Up] = 1;
  }

  if ((gamepad.device.directionmask & mask_dpad_down) ||
      (gamepad.device.directionmask & mask_stick_down)) {
    gamepad.device.states[InputState::Down] = 1;
  }

  if ((gamepad.device.directionmask & mask_dpad_left) ||
      (gamepad.device.directionmask & mask_stick_left)) {
    gamepad.device.states[InputState::Left] = 1;
  }

  if ((gamepad.device.directionmask & mask_dpad_right) ||
      (gamepad.device.directionmask & mask_stick_right)) {
    gamepad.device.states[InputState::Right] = 1;
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
