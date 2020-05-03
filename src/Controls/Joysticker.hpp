#pragma once
#include "Engine/InputDevice.hpp"
#include "Engine/ProgressBar.hpp"
#include "Player/Player.hpp"
namespace Senseless {
class Team;
enum class JoystickerState { InPossession, NotInPossession };

//
//
//
class Joysticker : public InputListener {
 public:
  //
  //
  //
  void connectDevice(InputDevice &in_device);
  //
  //
  //
  void update();
  //
  //
  //
  void onInputEvent(const InputEvent in_event,
                    const std::vector<int> &in_params) override;
  ProgressBar *power_bar = nullptr;
  InputDevice *input = nullptr;
  Player *player = nullptr;
  Team *team = nullptr;

 private:
  JoystickerState state = JoystickerState::InPossession;
};
}  // namespace Senseless
