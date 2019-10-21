#include "Gamepad.hpp"

#include <iostream>
namespace Engine {
//
//
//
void Gamepad::update(const sf::Event &in_event) {
  directionmask = mask_zero;
  buttonmask = mask_zero;

  set_button_mask();
  set_dpad_mask();
  set_stick_mask();
  check_event();
}
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

  if (sf::Joystick::isButtonPressed(sf_joystick_index, 6)) {
    buttonmask |= mask_back;
  }

  if (sf::Joystick::isButtonPressed(sf_joystick_index, 7)) {
    buttonmask |= mask_start;
  }

  // debug
//  for (int i=0;i<sf::Joystick::ButtonCount; ++i){
//    if(sf::Joystick::isButtonPressed(sf_joystick_index, i)){
//      std::cout << i <<std::endl;
//    }
//  }
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
//
//
//
void Gamepad::check_event() {
  // for the notifier
  std::vector<int> params;
  // if there was a cached tap, see if enough time has elapsed to make it a tap
  // now and not a possible double tap  if (fire_params.cached_tap) {
  if (fire_params.cached_tap &&
      ++fire_params.ticks_since_tap > fire_params.fire_double_tap_length) {
    // time up -> this is a tap and not a double tap
    fire_params.cached_tap = false;
    fire_params.ticks_since_tap = 0;
    ////////////////////////////////////////////////////////////
    notify(InputEvent::SingleTap, params);
    ////////////////////////////////////////////////////////////
  }

  // fire was up and is now down
  else if ((buttonmask & mask_a) && (old_buttonmask & mask_a) == 0) {
    fire_params.fire_ticks = 0;
    ////////////////////////////////////////////////////////////
    notify(InputEvent::FireDown, params);
    ////////////////////////////////////////////////////////////
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
      // was there a tap cached?
      if (fire_params.cached_tap) {
        // so this is a double tap
        fire_params.cached_tap = false;
        fire_params.ticks_since_tap = 0;
        ////////////////////////////////////////////////////////////
        notify(InputEvent::DoubleTap, params);
        ////////////////////////////////////////////////////////////
      } else {
        fire_params.cached_tap = true;
      }
    } else {
      ////////////////////////////////////////////////////////////
      notify(InputEvent::FireUp, params);
      ////////////////////////////////////////////////////////////
    }
  }
  // save old states to check for events
  old_buttonmask = buttonmask;
}
}  // namespace Engine
