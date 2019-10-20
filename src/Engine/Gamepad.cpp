#include "Gamepad.hpp"

#include <iostream>
namespace Engine {
//
//
//
void Gamepad::update(const sf::Event &in_event) {
  directionmask = mask_zero;
  buttonmask = mask_zero;
  resetStates();

  set_button_mask();
  set_dpad_mask();
  set_stick_mask();

  // check for a fire event

  // fire was up and is now down
  if ((buttonmask & mask_a) && (old_buttonmask & mask_a) == 0) {
    events[InputEvent::FireDown] = 1;
    fire_params.fire_ticks = 0;
    std::cout << "down" << std::endl;
  }

  // fire is still down
  else if (buttonmask & mask_a && (old_buttonmask & mask_a)) {
    fire_params.FireLength = fire_params.fire_ticks++;
  }

  // fire was down and is now up
  else if ((buttonmask & mask_a) == 0 && old_buttonmask & mask_a) {
    fire_params.FireLengthCached = fire_params.fire_ticks;
    fire_params.FireLength = 0;
    if (fire_params.fire_ticks < fire_params.fire_tap_length) {
      // cache the tap to detect a double tap
      fire_params.cached_tap = true;
      fire_params.fire_ticks = 0;
    } else {
      std::cout << "up" << std::endl;
    }
  }
  // save old states to check for events
  old_buttonmask = buttonmask;

  //
  // Fire event
  //
  // waiting to see if the release was quick enough to be a tap event
  //  if (fire_params.cached_tap) {
  //    if (++fire_params.ticks_since_tap > fire_params.fire_double_tap_length)
  //    {
  //      fire_params.cached_tap = false;
  //      fire_params.ticks_since_tap = 0;
  //      std::cout << "tap" << std::endl;
  //    }
  //  }
  //  if (old_events[InputEvent::FireDown]) {
  //    if (!events[InputEvent::FireDown]) {
  //      if (fire_params.FireLengthCached <= fire_params.fire_tap_length) {
  //        if (fire_params.cached_tap) {
  //          std::cout << "double tap" << std::endl;
  //          fire_params.cached_tap = false;
  //          fire_params.ticks_since_tap = 0;
  //        }
  //      } else {
  //        std::cout << "fire released" << std::endl;
  //      }
  //    }

  //  } else {
  //    if (events[InputEvent::FireDown]) {
  //      // start listening for a tap
  //      fire_params.cached_tap = true;
  //      std::cout << "cache tap" << std::endl;
  //      std::cout << "fire pressed" << std::endl;
  //    }
  //  }
}  // namespace Engine
//
//
//
void Gamepad::set_button_mask() {
  if (sf::Joystick::isButtonPressed(sf_joystick_index, 0)) {
    buttonmask |= mask_a;
  }

  if (sf::Joystick::isButtonPressed(sf_joystick_index, 1)) {
    buttonmask |= mask_b;
  }

  if (sf::Joystick::isButtonPressed(sf_joystick_index, 2)) {
    buttonmask |= mask_x;
  }

  if (sf::Joystick::isButtonPressed(sf_joystick_index, 3)) {
    buttonmask |= mask_y;
  }

  if (sf::Joystick::isButtonPressed(sf_joystick_index, 4)) {
    buttonmask |= mask_l1;
  }

  if (sf::Joystick::isButtonPressed(sf_joystick_index, 5)) {
    buttonmask |= mask_r1;
  }

  if (sf::Joystick::isButtonPressed(sf_joystick_index, 8)) {
    buttonmask |= mask_back;
  }

  if (sf::Joystick::isButtonPressed(sf_joystick_index, 9)) {
    buttonmask |= mask_start;
  }
}
//
//
//
void Gamepad::set_dpad_mask() {
  if (sf::Joystick::getAxisPosition(sf_joystick_index,
                                    sf::Joystick::Axis::PovX) < 0) {
    directionmask |= mask_dpad_left;
  }
  if (sf::Joystick::getAxisPosition(sf_joystick_index,
                                    sf::Joystick::Axis::PovX) > 0) {
    directionmask |= mask_dpad_right;
  }
  if (sf::Joystick::getAxisPosition(sf_joystick_index,
                                    sf::Joystick::Axis::PovY) < 0) {
    directionmask |= mask_dpad_up;
  }
  if (sf::Joystick::getAxisPosition(sf_joystick_index,
                                    sf::Joystick::Axis::PovY) > 0) {
    directionmask |= mask_dpad_down;
  }
}
//
//
//
void Gamepad::set_stick_mask() {
  if (sf::Joystick::getAxisPosition(sf_joystick_index, sf::Joystick::Y) <
      -thumbstick_threshold) {
    directionmask |= mask_stick_up;
  }

  if (sf::Joystick::getAxisPosition(sf_joystick_index, sf::Joystick::Y) >
      thumbstick_threshold) {
    directionmask |= mask_stick_down;
  }

  if (sf::Joystick::getAxisPosition(sf_joystick_index, sf::Joystick::X) <
      -thumbstick_threshold) {
    directionmask |= mask_stick_left;
  }

  if (sf::Joystick::getAxisPosition(sf_joystick_index, sf::Joystick::X) >
      thumbstick_threshold) {
    directionmask |= mask_stick_right;
  }
}
}  // namespace Engine
