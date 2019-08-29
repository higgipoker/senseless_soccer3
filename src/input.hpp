#pragma once
#include "camera.hpp"
#include "game.hpp"

#include <gamelib3/math/vector.hpp>

#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Joystick.hpp>

#include <cstring>
#include <iostream>
#include <map>
#include <set>
#include <string>

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
static const int fire_double_tap_length = 15;

/**
 * @brief The InputDevice struct
 */
struct InputDevice {
  int states[InputState::Totalevents]{};
  int fire_ticks = 0;
  bool cached_tap = false;
  int ticks_since_tap = 0;
};

/**
 * @brief The Keyboard struct
 */
struct Keyboard {
  InputDevice device;
};

/**
 * @brief The Gamepad struct
 */
struct Gamepad {
  InputDevice device;
  int sf_joystick_index = 0;
  float trigger_threshold = 0;
  float thumbstick_threshold = 50.0f;
};

// list of gamepads/joysticks
inline std::set<Gamepad *> gamepads;

// map entities to the device that controls them
inline std::map<Entity *, InputDevice *> controlled_entities;

// seems reasonable to have one global keyboard for our purposes
inline Keyboard keyboard;

void reset_device(InputDevice &device);
void init_gamepad(Gamepad &gamepad);
void handle_input(Game &game, Camera &camera);
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
void update_keyboard(Game &game);
void update_gamepad(Gamepad &gamepad);
void poll_controllers();
void update_controlled_entities();
