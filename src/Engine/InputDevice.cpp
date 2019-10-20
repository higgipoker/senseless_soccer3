#include "InputDevice.hpp"

#include <iostream>
namespace Engine {
//
//
//
void InputDevice::resetStates() {
  for (auto &state : events) {
    state.second = 0;
  }
}
//
//
//
bool InputDevice::up() { return directionmask & mask_dpad_up; }
//
//
//
bool InputDevice::down() { return directionmask & mask_dpad_down; }
//
//
//
bool InputDevice::left() { return directionmask & mask_dpad_left; }
//
//
//
bool InputDevice::right() { return directionmask & mask_dpad_right; }
//
//
//
bool InputDevice::fire_down() { return buttonmask & mask_a; }
//
//
//
void InputDevice::setListener(InputListener &in_listener) {
  if (listener) {
    std::cout << "InputDevice::setListener> changine listener" << std::endl;
  }
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
}  // namespace Engine
