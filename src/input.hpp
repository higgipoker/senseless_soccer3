#pragma once
#include "entity.hpp"
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

struct Gamepad {
  int states[InputState::Totalevents]{};
  int fire_ticks = 0;
  int sf_joystick_index = 0;
  float trigger_threshold = 0;
  float thumbstick_threshold = 50.0f;
  bool cached_tap = false;
  int ticks_since_tap = 0;
};

inline std::set<Gamepad *> controllers;
inline std::map<Entity *, Gamepad *> controlled_entities;

void handle_input(Game &game);
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

inline void poll_controllers() {
  for (auto &controller : controllers) {
    update(*controller);
  }
}
inline void update_controlled_entities() {
  for (auto &entry : controlled_entities) {
    if (entry.second->states[InputState::Left]) {
      apply_force(*entry.first, gamelib3::Vector3(-1, 0));
    }
    if (entry.second->states[InputState::Right]) {
      apply_force(*entry.first, gamelib3::Vector3(1, 0));
    }
    if (entry.second->states[InputState::Up]) {
      apply_force(*entry.first, gamelib3::Vector3(0, -1));
    }
    if (entry.second->states[InputState::Down]) {
      apply_force(*entry.first, gamelib3::Vector3(0, 1));
    }
  }
}
