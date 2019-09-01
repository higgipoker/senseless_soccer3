#pragma once

#include "input.hpp"

#include <SFML/Window/Keyboard.hpp>

#include <map>
inline std::map<InputState, sf::Keyboard::Key> keymap{
    {InputState::Up, sf::Keyboard::W},
    {InputState::Left, sf::Keyboard::A},
    {InputState::Down, sf::Keyboard::S},
    {InputState::Right, sf::Keyboard::D},
    {InputState::FireDown, sf::Keyboard::Up}};

/**
 * @brief update_keyboard
 */
void update_keyboard();
