#include "keyboard.hpp"

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void update_keyboard() {
  std::fill(std::begin(keyboard.device.states),
            std::end(keyboard.device.states), 0);
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
    keyboard.device.directionmask |= mask_dpad_left;
    keyboard.device.states[InputState::Left] = 1;
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
    keyboard.device.directionmask |= mask_dpad_right;
    keyboard.device.states[InputState::Right] = 1;
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
    keyboard.device.directionmask |= mask_dpad_up;
    keyboard.device.states[InputState::Up] = 1;
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
    keyboard.device.directionmask |= mask_dpad_down;
    keyboard.device.states[InputState::Down] = 1;
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
    keyboard.device.directionmask |= mask_dpad_down;
    keyboard.device.states[InputState::FireDown] = 1;
  }
}
