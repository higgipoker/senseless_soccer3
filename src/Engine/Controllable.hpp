#pragma once
#include "InputDevice.hpp"
namespace Engine {
//
//
//
class Controllable : public InputListener {
 public:
  //
  //
  //
  Controllable();
  //
  //
  //
  virtual void handleInput() = 0;
  //
  //
  //
  void attachInput(InputDevice &in_device);
  //
  //
  //
  void detachInput();
  //
  //
  //
  bool isInputAttached();
  //
  //
  //
  InputDevice &getInputDevice() const;
  //
  //
  //
  void onInputEvent(const InputEvent in_event,
                    const std::vector<int> &in_params) override{};

 protected:
  InputDevice *input = nullptr;
};
}  // namespace Engine
