#include "Controllable.hpp"

#include <cassert>
namespace Senseless {
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
  input->detatchListener(*this);
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
}  // namespace Senseless
