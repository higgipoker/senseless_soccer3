#include "Joysticker.hpp"

#include "Match/Match.hpp"
#include "Team/Team.hpp"

using namespace Engine;
//
//
//
void Joysticker::connectDevice(InputDevice &in_device) {
    input = &in_device;
}
//
//
//
void Joysticker::update() {
}
//
//
//
void Joysticker::onInputEvent(const InputEvent in_event, const std::vector<int> &in_params) {
    switch (in_event) {
        case InputEvent::FireDown:
            if (power_bar) {
                power_bar->start();
            }
            break;

        case InputEvent::FireUp: {
            if (power_bar) {
                power_bar->stop();
                power_bar->reset();
            }
        } break;

        case InputEvent::DoubleTap:
            if (power_bar) {
                power_bar->stop();
                power_bar->reset();
            }
            break;

        case InputEvent::SingleTap:
            if (power_bar) {
                power_bar->stop();
                power_bar->reset();
            }
            break;
    }
}
