#pragma once
#include "InputDevice.hpp"

namespace Engine {
//
//
//
class Gamepad : public InputDevice {
 public:
  //
  //
  //
  Gamepad() = default;
  //
  //
  //
  void update() override;

 protected:
  int sf_joystick_index = 0;
  float thumbstick_threshold = 50.0f;
  //
  //
  //
  void set_button_mask();
  //
  //
  //
  void set_dpad_mask();
  //
  //
  //
  void set_stick_mask();
  //
  //
  //
  void check_event();
};
}  // namespace Engine
