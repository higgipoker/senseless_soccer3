#pragma once
#include "Engine/InputDevice.hpp"

#include "Engine/ProgressBar.hpp"
#include "Player/Player.hpp"

class Team;
enum class JoystickerState { InPossession, NotInPossession };

//
//
//
class Joysticker : public Engine::InputListener {
   public:
    //
    //
    //
    void connectDevice(Engine::InputDevice &in_device);
    //
    //
    //
    void update();
    //
    //
    //
    void onInputEvent(const Engine::InputEvent in_event, const std::vector<int> &in_params) override;
    Engine::ProgressBar *power_bar = nullptr;
    Engine::InputDevice *input = nullptr;
    Player *player = nullptr;
    Team *team = nullptr;

   private:
    JoystickerState state = JoystickerState::InPossession;
};
