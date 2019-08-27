#pragma once
#include "game.hpp"
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Joystick.hpp>
#include <cstring>
#include <iostream>
#include <map>
#include <string>

namespace Input {

/**
 * @brief The InputState enum
 */
enum InputState {
  Up = 0,
  Down,
  Left,
  Right,

  FireDown,
  FireUp,
  FireLength,
  FireLengthCached,
  SingleTap,
  DoubleTap,
  FirePress,

  FireDown2,
  FireUp2,
  FireLength2,
  FireLengthCached2,
  SingleTap2,
  DoubleTap2,
  FirePress2,

  FireDown3,
  FireUp3,
  FireLength3,
  FireLengthCached3,
  SingleTap3,
  DoubleTap3,
  FirePress3,

  FireDown4,
  FireUp4,
  FireLength4,
  FireLengthCached4,
  SingleTap4,
  DoubleTap4,
  FirePress4,

  Totalevents
};

/**
 * @brief The ControllerEventID enum
 */
enum class ControllerEventID {
  NoEvent = 0,
  Fire,
  FireTap,
  DPadLeft,
  DPadRight,
  DPadUp,
  DPadDown
};

/**
 * @brief The ControllerEventStatus enum
 */
enum class ControllerEventStatus { Released = 0, Pressed };

/**
 * @brief The ControllerEvent struct
 */
struct ControllerEvent {
  ControllerEventID id = ControllerEventID::NoEvent;
  ControllerEventStatus status = ControllerEventStatus::Released;
  int param = 0;
};
static const int fire_tap_length = 5;

struct Gamepad {
  int states[InputState::Totalevents];
  int fire_ticks = 0;
  int sf_joystick_index = 0;
  float trigger_threshold = 0;
  float thumbstick_threshold = 50.0f;
};
void handle_input(Game &game, Input::Gamepad &gamepad) ;
void init(Gamepad &gamepad);
bool isConnected(Gamepad &gamepad);
bool A(Gamepad &gamepad);
bool B(Gamepad &gamepad);
bool X(Gamepad &gamepad);
bool Y(Gamepad &gamepad);
bool LeftBumper(Gamepad &gamepad);
bool RightBumper(Gamepad &gamepad);
bool LeftTriggerPressed(Gamepad &gamepad);
bool RightTriggerPressed(Gamepad &gamepad);
bool Back(Gamepad &gamepad);
bool Start(Gamepad &gamepad);
bool XboxButton(Gamepad &gamepad);
bool LeftThumbstickClick(Gamepad &gamepad);
bool RightThumbstickClick(Gamepad &gamepad);
bool DpadLeft(Gamepad &gamepad);
bool DpadRight(Gamepad &gamepad);
bool DpadUp(Gamepad &gamepad);
bool DpadDown(Gamepad &gamepad);
float LeftTriggerValue(Gamepad &gamepad);
float RightTriggerValue(Gamepad &gamepad);
bool LeftTrigger(Gamepad &gamepad);
bool RightTrigger(Gamepad &gamepad);
sf::Vector2f LeftThumbstick(Gamepad &gamepad);
sf::Vector2f RightThumbstick(Gamepad &gamepad);
bool UniUp(Gamepad &gamepad);
bool UniDown(Gamepad &gamepad);
bool UniLeft(Gamepad &gamepad);
bool UniRight(Gamepad &gamepad);
void update(Gamepad &gamepad);
}  // namespace Input
