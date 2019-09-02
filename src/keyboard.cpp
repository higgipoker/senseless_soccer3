#include "keyboard.hpp"
//
//
//
void update_keyboard() {
  std::fill(std::begin(keyboard.device.states),
            std::end(keyboard.device.states), 0);

  if (sf::Keyboard::isKeyPressed(keymap[InputState::Left])) {
    keyboard.device.directionmask |= mask_dpad_left;
    keyboard.device.states[InputState::Left] = 1;
  }
  if (sf::Keyboard::isKeyPressed(keymap[InputState::Right])) {
    keyboard.device.directionmask |= mask_dpad_right;
    keyboard.device.states[InputState::Right] = 1;
  }
  if (sf::Keyboard::isKeyPressed(keymap[InputState::Up])) {
    keyboard.device.directionmask |= mask_dpad_up;
    keyboard.device.states[InputState::Up] = 1;
  }
  if (sf::Keyboard::isKeyPressed(keymap[InputState::Down])) {
    keyboard.device.directionmask |= mask_dpad_down;
    keyboard.device.states[InputState::Down] = 1;
  }
  if (sf::Keyboard::isKeyPressed(keymap[InputState::FireDown])) {
    keyboard.device.directionmask |= mask_dpad_down;
    keyboard.device.states[InputState::FireDown] = 1;
  }
}
