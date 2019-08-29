#pragma once

#include "input.hpp"

// list of gamepads/joysticks
inline std::set<Gamepad *> gamepads;
/**
 * @brief get_joystick_ids
 * @return
 */
std::array<int, MAX_JOYSTICKS> get_joystick_ids();
/**
 * @brief init_gamepad
 * @param gamepad
 */
void init_gamepad(Gamepad &gamepad);
/**
 * @brief init_gamepad
 * @param gamepad
 */
void init_gamepad(Gamepad &gamepad);
/**
 * @brief isConnected
 * @param gamepad
 * @return
 */
bool isConnected(Gamepad &gamepad);
/**
 * @brief set_button_mask
 * @param gamepad
 */
void set_button_mask(Gamepad &gamepad);
/**
 * @brief set_dpad_mask
 * @param gamepad
 */
void set_dpad_mask(Gamepad &gamepad);
/**
 * @brief update_gamepad
 * @param gamepad
 */
void update_gamepad(Gamepad &gamepad);
