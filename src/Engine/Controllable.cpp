#include "Controllable.hpp"

#include <cassert>
namespace Engine {
//
//
//
Controllable::Controllable() {}
//
//
//
void Controllable::attachInput(InputDevice &in_device) {
  input = &in_device;
  in_device.attachListener(*this);
}
//
//
//
void Controllable::detachInput() {
  assert("input is null" && input);
  input = nullptr;
}
//
//
//
InputDevice &Controllable::getInputDevice() const {
  assert(
      "No input device is attached to this Controllable, call isInputAttached "
      "first." &&
      input);
  return *input;
}
//
//
//
bool Controllable::isInputAttached() { return input != nullptr; }
}  // namespace Engine
