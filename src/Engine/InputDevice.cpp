#include "InputDevice.hpp"

#include <iostream>
namespace Engine {
//
//
//
bool InputDevice::up() {
  return directionmask & mask_dpad_up || directionmask & mask_stick_up;
}
//
//
//
bool InputDevice::down() {
  return directionmask & mask_dpad_down || directionmask & mask_stick_down;
}
//
//
//
bool InputDevice::left() {
  return directionmask & mask_dpad_left || directionmask & mask_stick_left;
}
//
//
//
bool InputDevice::right() {
  return directionmask & mask_dpad_right || directionmask & mask_stick_right;
}
//
//
//
bool InputDevice::fireDown() { return buttonmask & mask_a; }
//
//
//
void InputDevice::setListener(InputListener &in_listener) {
  listener = &in_listener;
}
//
//
//
void InputDevice::notify(const InputEvent in_event,
                         const std::vector<int> &in_params) {
  if (listener) {
    listener->onEvent(in_event, in_params);
  }
}
//
//
//
bool InputDevice::isButtonPressed(const unsigned char in_which) {
  return in_which & buttonmask;
}
}  // namespace Engine
