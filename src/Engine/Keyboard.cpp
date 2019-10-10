#include "Keyboard.hpp"

namespace Engine {
//
//
//
void Keyboard::update(const sf::Event& in_event) {
  directionmask = mask_zero;
  std::fill(std::begin(states), std::end(states), 0);
  if (sf::Keyboard::isKeyPressed(keymap[InputState::Left])) {
    directionmask |= mask_dpad_left;
    states[InputState::Left] = 1;
  }
  if (sf::Keyboard::isKeyPressed(keymap[InputState::Right])) {
    directionmask |= mask_dpad_right;
    states[InputState::Right] = 1;
  }
  if (sf::Keyboard::isKeyPressed(keymap[InputState::Up])) {
    directionmask |= mask_dpad_up;
    states[InputState::Up] = 1;
  }
  if (sf::Keyboard::isKeyPressed(keymap[InputState::Down])) {
    directionmask |= mask_dpad_down;
    states[InputState::Down] = 1;
  }
}
//
//
//
bool Keyboard::up() { return directionmask & mask_dpad_up; }
//
//
//
bool Keyboard::down() { return directionmask & mask_dpad_down; }
//
//
//
bool Keyboard::left() { return directionmask & mask_dpad_left; }
//
//
//
bool Keyboard::right() { return directionmask & mask_dpad_right; }
}  // namespace Engine
